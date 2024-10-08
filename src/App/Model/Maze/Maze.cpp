/**
 * @file Maze.cpp
 * @brief Implementation of the class Maze
 */

#include "Maze.h"

#include <sys/stat.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace s21 {

/**
 * @brief Default constructor
 */
Maze::Maze()
    : verticalMatrix_(), horizontalMatrix_(), pathFinder_(new PathFinder()) {}

/**
 * @brief Default destructor
 */
Maze::~Maze() { delete pathFinder_; }

/**
 * @brief Load maze from file
 * @param path - path to the file
 * @return Operation result
 */
OpResult Maze::load(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) return {false, "File not found"};

  int rows = 0, cols = 0;

  file >> rows >> cols;

  if ((rows <= 0 || cols <= 0) || (rows > 50 || cols > 50))
    return {false, "Incorrect maze size"};

  file >> std::ws;

  verticalMatrix_.Resize(rows, cols);

  std::string line("");

  for (int i = 0; i < rows; i++) {
    std::getline(file, line);
    std::istringstream iss(line);

    for (int j = 0; j < cols; j++) {
      char token = 0;
      iss >> token;

      if (token != '0' && token != '1') {
        clear();
        return {false, "Invalid maze data"};
      }

      verticalMatrix_(i, j) = token;
    }
  }

  file >> std::ws;

  line.clear();

  horizontalMatrix_.Resize(rows, cols);

  for (int i = 0; i < rows; i++) {
    std::getline(file, line);
    std::istringstream iss(line);

    for (int j = 0; j < cols; j++) {
      char token = 0;
      iss >> token;

      if (token != '0' && token != '1') {
        clear();
        return {false, "Invalid maze data"};
      }

      horizontalMatrix_(i, j) = token;
    }
  }

  loadMazeForPathFinder();

  Observable::notifyUpdate();

  return {true, ""};
}

/**
 * @brief Clear the maze
 */
void Maze::clear() {
  verticalMatrix_.Resize(0, 0);
  horizontalMatrix_.Resize(0, 0);
}

/**
 * @brief Generate maze
 * @param rows - number of rows
 * @param cols - number of columns
 * @return Operation result
 */
OpResult Maze::generate(int rows, int cols) {
  if ((rows <= 0 || cols <= 0) || (rows > 50 || cols > 50))
    return {false, "Incorrect maze size"};

  MazeGenerator generator(verticalMatrix_, horizontalMatrix_, rows, cols);

  OpResult result = generator.generate();

  if (result.IsSuccess()) {
    save();
    loadMazeForPathFinder();
    Observable::notifyUpdate();
  }

  return result;
}

/**
 * @brief Save the maze to file
 */
void Maze::save() {
  static std::size_t mazeCounter = 0;

  if (!std::filesystem::exists("./generatedMazes"))
    std::filesystem::create_directory("./generatedMazes");

  std::string fileName =
      "./generatedMazes/maze_" + std::to_string(mazeCounter++) + ".txt";

  std::ofstream file(fileName);

  file << verticalMatrix_.GetRows() << " " << verticalMatrix_.GetCols()
       << std::endl;

  loadMatrixToFile(verticalMatrix_, file, false);

  file << std::endl;

  loadMatrixToFile(horizontalMatrix_, file, true);
}

/**
 * @brief Load maze for path finder
 */
void Maze::loadMatrixToFile(const S21Matrix<char> &matrix, std::ofstream &file,
                            bool eof) {
  int rows = matrix.GetRows();
  int cols = matrix.GetCols();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (j == cols - 1)
        file << matrix(i, j);
      else
        file << matrix(i, j) << " ";
    }

    if (!(i == rows - 1 && eof)) file << std::endl;
  }
}

/**
 * @brief Get the path
 * @param width - width of the area
 * @param height - height of the area
 * @return Vector of walls
 */
std::vector<Line> Maze::get(float width, float height) {
  float rows = verticalMatrix_.GetRows();
  float cols = verticalMatrix_.GetCols();

  std::vector<Line> lines;

  if (!rows || !cols) return lines;

  lines.reserve(rows * cols + 4);

  lines.push_back({0.0f, 1.0f, width, 1.0f});
  lines.push_back({1.0f, height, 1.0f, 0.0f});
  lines.push_back({width - 1.0f, height - 1.0f, 0.0f, height - 1.0f});
  lines.push_back({width - 1.0f, 0.0f, width - 1.0f, height - 1.0f});

  float baseCellSize = std::min(width / rows, height / cols);

  // Calculate scaling factors to maintain aspect ratio within each cell
  float scaleFactorX = width / (baseCellSize * cols);
  float scaleFactorY = height / (baseCellSize * rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float x0 = baseCellSize * j * scaleFactorX;
      float y0 = baseCellSize * i * scaleFactorY;
      float x1 = baseCellSize * (j + 1.0f) * scaleFactorX;
      float y1 = baseCellSize * (i + 1.0f) * scaleFactorY;

      if (verticalMatrix_(i, j) == '1' && j != cols - 1)
        lines.push_back({x1, y0, x1, y1});

      if (horizontalMatrix_(i, j) == '1' && i != rows - 1)
        lines.push_back({x0, y1, x1, y1});
    }
  }

  return lines;
}

/**
 * @brief Set the start position of the path
 * @param p - start position
 * @param width - width of the area
 * @param height - height of the area
 */
void Maze::setStartPosition(Point<float> p, float width, float height) {
  pathFinder_->setStartPosition(p, width / verticalMatrix_.GetCols(),
                                height / verticalMatrix_.GetRows());
}

/**
 * @brief Set the end position of the path
 * @param p - end position
 * @param width - width of the area
 * @param height - height of the area
 */
void Maze::setEndPosition(Point<float> p, float widht, float height) {
  pathFinder_->setEndPosition(p, widht / verticalMatrix_.GetCols(),
                              height / verticalMatrix_.GetRows());
}

/**
 * @brief Get the maze path
 */
PathRenderConfig Maze::getPath(float width, float height) {
  return pathFinder_->get(Point<float>{width, height});
}

/**
 * @brief Find the path through the Q-Learning algorithm
 * @param start - start position
 * @param end - end position
 * @return Operation result
 */
OpResult Maze::QPathFinding(Point<int> start, Point<int> end) {
  OpResult result = pathFinder_->QPathFinding(start, end);

  if (result.IsSuccess()) Observable::notifyUpdate();

  return result;
}

/**
 * @brief Clear the path
 */
void Maze::clearPath() {
  pathFinder_->reset();
  Observable::notifyUpdate();
}

/**
 * @brief Save the matrix to file
 * @param matrix - matrix
 * @param path - path to the file
 * @param eof - end of file
 */
void Maze::loadMazeForPathFinder() {
  int rows = verticalMatrix_.GetRows();
  int cols = verticalMatrix_.GetCols();

  S21Matrix<char> matrix_(rows * 2, cols * 2);
  matrix_.FillNumbers('1');

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_(i * 2, j * 2) = '0';

      if (j < cols - 1) matrix_(i * 2, j * 2 + 1) = verticalMatrix_(i, j);

      if (i < rows - 1) matrix_(i * 2 + 1, j * 2) = horizontalMatrix_(i, j);
    }
  }

  pathFinder_->setMaze(std::move(matrix_));
}
}  // namespace s21