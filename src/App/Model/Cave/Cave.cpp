/**
 * @file Cave.cpp
 * @brief The implementation of the class Cave
 */

#include "Cave.h"

#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <thread>

#include "../FileReader/FileReader.h"

namespace s21 {

/**
 * @brief Default constructor
 */
Cave::Cave() : caveMatrix_() {}

/**
 * @brief The load method cave from file
 * @param path - path to the file
 * @return Operation result
 */
OpResult Cave::load(const std::string &path) {
  FileReader reader(path);
  if (!reader.file.is_open()) return {false, "File not found"};

  size_t rows = 0, cols = 0;

  reader.file >> rows >> cols;

  if (rows <= 0 || rows > 50 || cols <= 0 || cols > 50)
    return {false, "Incorrect cave size"};

  reader.file >> std::ws;

  caveMatrix_.Resize(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    std::string line("");
    std::getline(reader.file, line);
    std::istringstream iss(line);

    for (size_t j = 0; j < cols; j++) {
      char token = 0;
      iss >> token;

      if (token != '0' && token != '1') return {false, "Invalid cave data"};

      caveMatrix_(i, j) = token;
    }
  }

  Observable::notifyUpdate();

  return {true, ""};
}

/**
 * @brief The generate method cave
 * @param rows - number of rows
 * @param cols - number of columns
 * @param initChance - chance of initial living cells
 * @return Operation result
 */
OpResult Cave::generate(int rows, int cols, int initChance) {
  if (rows <= 0 || cols <= 0 || rows > 50 || cols > 50)
    return {false, "Incorrect cave size"};

  if (initChance <= 0 || initChance > 100)
    return {false, "Incorrect init chance"};

  caveMatrix_.Resize(rows, cols);
  caveMatrix_.FillNumbers('0');

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(0, 99);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (distribution(gen) < initChance) caveMatrix_(i, j) = '1';

  Observable::notifyUpdate();

  return {true, ""};
}

/**
 * @brief Parameters check
 * @param birthLimit - birth limit
 * @param deathLimit - death limit
 * @param time - time
 * @return Operation result
 */
OpResult Cave::parametersCheck(int birthLimit, int deathLimit, int time) {
  if (caveMatrix_.GetRows() < 1) return {false, "Cave is empty"};

  if ((birthLimit < 0 || deathLimit < 0) || (birthLimit > 7 || deathLimit > 7))
    return {false, "Incorrect limits"};

  if (time < 0) return {false, "Incorrect time"};

  return {true, ""};
}

/**
 * @brief The transform method cave
 * @param full - is full transform or not
 * @param birthLimit - birth limit
 * @param deathLimit - death limit
 * @param time - time in milliseconds
 * @return Operation result
 */
OpResult Cave::transform(bool full, int birthLimit, int deathLimit, int time) {
  if (OpResult res = parametersCheck(birthLimit, deathLimit, time);
      !res.IsSuccess())
    return res;

  int iterations = full ? 100 : 1;

  for (int i = 0; i < iterations; i++) {
    S21Matrix<char> last = full ? caveMatrix_ : S21Matrix<char>{};

    oneStepTransform(birthLimit, deathLimit);

    if (full && caveMatrix_ == last) break;

    std::this_thread::sleep_for(std::chrono::milliseconds(time));
  }

  return {true, ""};
}

/**
 * @brief One step transform cave
 * @param birthLimit - birth limit
 * @param deathLimit - death limit
 */
void Cave::oneStepTransform(int birthLimit, int deathLimit) {
  int rows = caveMatrix_.GetRows();
  int cols = caveMatrix_.GetCols();

  S21Matrix<char> buffer(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int count = countLivingNeighbors(i, j);

      if (caveMatrix_(i, j) == '1')  // Living
        if (count < deathLimit) caveMatrix_(i, j) = '0';

      if (caveMatrix_(i, j) == '0')  // Dead
        if (count > birthLimit) caveMatrix_(i, j) = '1';
    }
  }

  Observable::notifyUpdate();
}

/**
 * @brief Count living neighbors
 * @param field - field
 * @param row - row
 * @param col - column
 * @return Count of living neighbors
 */
int Cave::countLivingNeighbors(int row, int col) {
  int rows = caveMatrix_.GetRows();
  int cols = caveMatrix_.GetCols();

  int count = 0;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if (x == 0 && y == 0) continue;

      Point<int> point = {col + x, row + y};

      if (point.col < 0 || point.row < 0 || point.col >= cols ||
          point.row >= rows) {
        count++;
      } else
        count += caveMatrix_(point.row, point.col) == '1' ? 1 : 0;
    }
  }

  return count;
}

/**
 * @brief The get method cave
 * @param width - width of the cave
 * @param height - height of the cave
 * @return Vector of cells
 */
std::vector<Rect> Cave::get(float width, float height) {
  float rows = caveMatrix_.GetRows();
  float cols = caveMatrix_.GetCols();

  if (!rows || !cols) return {};

  std::vector<Rect> lines;

  lines.reserve(rows * cols + 4);

  float baseCellSize = std::min(width / rows, height / cols);

  // Calculate scaling factors to maintain aspect ratio within each cell
  float scaleFactorX = width / (baseCellSize * cols);
  float scaleFactorY = height / (baseCellSize * rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (caveMatrix_(i, j) == '1') {
        float x0 = baseCellSize * j * scaleFactorX;
        float y0 = baseCellSize * i * scaleFactorY;
        float width = baseCellSize * scaleFactorX + 1.0f;
        float height = baseCellSize * scaleFactorY + 1.0f;

        lines.push_back({x0, y0, width, height});
      }
    }
  }

  return lines;
}
}  // namespace s21