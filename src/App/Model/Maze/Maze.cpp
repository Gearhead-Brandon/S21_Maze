#include "Maze.h"
#include "../FileReader/FileReader.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>

namespace s21{
    Maze::Maze() 
        : verticalMatrix_()
        , horizontalMatrix_()
        , pathFinder_(new PathFinder()){}

    Maze::~Maze() {
        delete pathFinder_;
    }

    OpResult Maze::load(const std::string &path){
        FileReader reader(path);
        if (!reader.file.is_open())
            return {false, "File not found"};

        int rows = 0, cols = 0;

        reader.file >> rows >> cols;

        if ((rows <= 0 || cols <= 0) || (rows > 50 || cols > 50))
            return {false, "Incorrect maze size"};

        reader.file >> std::ws;

        verticalMatrix_.Resize(rows, cols);

        std::string line("");

        for (int i = 0; i < rows; i++){
            std::getline(reader.file, line);
            std::istringstream iss(line);

            for (int j = 0; j < cols; j++){
                char token = 0;
                iss >> token;

                if (token != '0' && token != '1'){
                    clear();
                    return {false, "Invalid maze data"};
                }

                verticalMatrix_(i, j) = token;
            }
        }

        reader.file >> std::ws;

        line.clear();

        horizontalMatrix_.Resize(rows, cols);

        for (int i = 0; i < rows; i++){
            std::getline(reader.file, line);
            std::istringstream iss(line);

            for (int j = 0; j < cols; j++){
                char token = 0;
                iss >> token;

                if (token != '0' && token != '1'){
                    clear();
                    return {false, "Invalid maze data"};
                }

                horizontalMatrix_(i, j) = token;
            }
        }

        loadMazeForPathFinder();

        // S21Matrix<char> matrix_(rows * 2 + 1, cols * 2 + 1);
        // matrix_.FillNumbers('1');

        // for(int i = 0; i < rows; i++){
        //     for(int j = 0; j < cols; j++){

        //         matrix_(i * 2 + 1,j * 2 + 1) = '0'; // Проходы

        //         // Вертикальные стены справа
        //         if(j < cols - 1)
        //             matrix_(i * 2 + 1,j * 2 + 2) = verticalMatrix_(i,j);

        //         // Горизонтальные стены снизу
        //         if(i < rows - 1)
        //             matrix_(i * 2 + 2,j * 2 + 1) = horizontalMatrix_(i,j);

        //         if(i == 0)
        //             matrix_(i * 2,j * 2) = '1'; // Верхняя стена

        //         if(j == 0)
        //             matrix_(i * 2,j * 2) = '1'; // Левая стена
        //     }
        // }

        // std::cout << std::endl;
        // for(int i = 0; i < matrix_.GetRows(); i++){
        //     for(int j = 0; j < matrix_.GetCols(); j++){
        //         if(matrix_(i,j) == '1')
        //             std::cout << "* ";
        //         else
        //             std::cout << "  ";
        //     }
        //     std::cout << std::endl;
        // }

        //reader.file.close();

        Observable::notifyUpdate();

        return {true, ""};
    }

    void Maze::clear(){
        verticalMatrix_.Resize(0, 0);
        horizontalMatrix_.Resize(0, 0);
    }

    OpResult Maze::generate(int rows, int cols){
        if ((rows <= 0 || cols <= 0) || (rows > 50 || cols > 50))
            return {false, "Incorrect maze size"};

        MazeGenerator generator(verticalMatrix_, horizontalMatrix_, rows, cols);

        OpResult result = generator.generate();

        if(result.IsSuccess()){
            save();
            loadMazeForPathFinder();
            Observable::notifyUpdate();
        }

        return result;
    }

    void Maze::save(){
        static std::size_t mazeCounter = 0;

        if (!std::filesystem::exists("./generatedMazes"))
            std::filesystem::create_directory("./generatedMazes");

        std::string fileName = "./generatedMazes/maze_" + std::to_string(mazeCounter++) + ".txt";

        std::ofstream file(fileName);

        file << verticalMatrix_.GetRows() << " " << verticalMatrix_.GetCols() << std::endl;

        loadMatrixToFile(verticalMatrix_, file, false);

        file << std::endl;

        loadMatrixToFile(horizontalMatrix_, file, true);

        file.close();
    }

    void Maze::loadMatrixToFile(const S21Matrix<char> &matrix, std::ofstream &file, bool eof){
        int rows = matrix.GetRows();
        int cols = matrix.GetCols();

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (j == cols - 1)
                    file << matrix(i, j);
                else
                    file << matrix(i, j) << " ";
            }

            if(!(i == rows - 1 && eof))
                file << std::endl;
        }
    }

    std::vector<Line> Maze::get(float width, float height){
        float rows = verticalMatrix_.GetRows();
        float cols = verticalMatrix_.GetCols();

        std::vector<Line> lines;

        if (!rows || !cols)
            return lines;

        lines.reserve(rows * cols + 4);

        lines.push_back({0.0f, 1.0f, width, 1.0f});
        lines.push_back({1.0f, height, 1.0f, 0.0f});
        lines.push_back({width - 1.0f, height - 1.0f, 0.0f, height - 1.0f});
        lines.push_back({width - 1.0f, 0.0f, width - 1.0f, height - 1.0f});

        float baseCellSize = std::min(width / rows, height / cols);

        // Calculate scaling factors to maintain aspect ratio within each cell
        float scaleFactorX = width / (baseCellSize * cols);
        float scaleFactorY = height / (baseCellSize * rows);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
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

    void Maze::setStartPosition(Point<float> p, float width, float height){
        // if(verticalMatrix_.GetRows() == 0)
        //     return;

        pathFinder_->setStartPosition(p, width / verticalMatrix_.GetCols(), height / verticalMatrix_.GetRows());
    }

    void Maze::setEndPosition(Point<float> p, float widht, float height){
        // if(verticalMatrix_.GetRows() == 0)
        //     return;

        pathFinder_->setEndPosition(p, widht / verticalMatrix_.GetCols(), height / verticalMatrix_.GetRows());
    }

    PathRenderConfig Maze::getPath(float width, float height){
        // if(verticalMatrix_.GetRows() == 0)
        //     return {};

        return pathFinder_->get( Point<float>{width, height} );

        // PathRenderConfig conf = pathFinder_->getPath( Point<float>{width, height} );

        // return conf;
    }

    void Maze::QPathFinding(Point<int> start, Point<int> end){
        pathFinder_->QPathFinding(start, end);
        Observable::notifyUpdate();
    }

    void Maze::clearPath(){
        pathFinder_->reset();
        Observable::notifyUpdate();
    }

    void Maze::loadMazeForPathFinder(){
        // if(verticalMatrix_.GetRows() == 0)
        //     return ;

        int rows = verticalMatrix_.GetRows();
        int cols = verticalMatrix_.GetCols();

        S21Matrix<char> matrix_(rows * 2 , cols * 2 );
        matrix_.FillNumbers('1');

        for (int i = 0; i < rows ; i++) {
            for (int j = 0; j < cols ; j++) {
                matrix_(i * 2  ,j * 2 ) = '0'; // Проходы

                if (j < cols - 1)
                    matrix_(i * 2  , j * 2 + 1) = verticalMatrix_(i, j);

                if (i < rows - 1)
                    matrix_(i * 2 + 1, j * 2) = horizontalMatrix_(i, j);
            }
        }

        pathFinder_->setMaze(std::move(matrix_));

        // std::cout << std::endl;
        // for(int i = 0; i < matrix_.GetRows() ; i++){
        //     for(int j = 0; j < matrix_.GetCols() ; j++){
        //         if(matrix_(i,j) == '1')
        //             std::cout << "*";
        //         else
        //             std::cout << "@";
        //     }
        //     std::cout << std::endl;
        // }
    }

}