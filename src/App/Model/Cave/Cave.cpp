#include "Cave.h"
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <thread>

namespace s21{

    Cave::Cave() : caveMatrix_() {}

    Cave::~Cave() {}

    OpResult Cave::load(const std::string &path) {
        std::ifstream file(path);
        if (!file.is_open())
            return {false, "File not found"};

        size_t rows = 0, cols = 0;

        file >> rows >> cols;

        if ((rows <= 0 || cols <= 0) || (rows > 50 || cols > 50))
            return {false, "Incorrect maze size"};

        file >> std::ws;

        caveMatrix_.Resize(rows, cols);

        for (size_t i = 0; i < rows; i++) {
            std::string line("");
            std::getline(file, line);
            std::istringstream iss(line);

            for (size_t j = 0; j < cols; j++) {
            
                char token = 0;
                iss >> token;

                if (token != '0' && token != '1')
                    return {false, "Invalid cave data"};
                
                caveMatrix_(i, j) = token;
            }
        }

        file.close();
        
        Observable::notifyUpdate();

        return {true, ""};
    }

    OpResult Cave::generate(int rows, int cols, int initChance){
        if (rows <= 0 || cols <= 0 || rows > 50 || cols > 50)
            return {false, "Incorrect maze size"};

        if(initChance <= 0 || initChance > 100)
            return {false, "Incorrect init chance"};

        caveMatrix_.Resize(rows, cols);
        caveMatrix_.FillNumbers('0');

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 99); // Диапазон от 0 до 99

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (distribution(gen) < initChance)
                    caveMatrix_(i, j) = '1';
            }
        }

        Observable::notifyUpdate();

        return {true, ""};
    }

    OpResult Cave::transform(int birthLimit, int deathLimit, int time){
        if((birthLimit < 0 || deathLimit < 0) || (birthLimit > 7 || deathLimit > 7))
            return {false, "Incorrect limits"};

        if(caveMatrix_.GetRows() < 1)
            return {false, "Cave is empty"};

        if(time < 0)
            return {false, "Incorrect time"};

        bool isSuccess = true;

        static int counter = 0;
        counter = 0;
        
        while(isSuccess){
            if(counter >= 200)
                break;

            S21Matrix<char> temp(caveMatrix_);

            transform(birthLimit, deathLimit);

            if(caveMatrix_ == temp)
                break;

            counter++;

            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }

        return {true, ""};
    }

    OpResult Cave::transform(int birthLimit, int deathLimit){
        if((birthLimit < 0 || deathLimit < 0) || (birthLimit > 7 || deathLimit > 7))
            return {false, "Incorrect limits"};

        if(caveMatrix_.GetRows() < 1)
            return {false, "Cave is empty"};

        int rows = caveMatrix_.GetRows();
        int cols = caveMatrix_.GetCols();

        S21Matrix<char> buffer(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int count = countLivingNeighbors(buffer, i, j);

                // if (caveMatrix_(i, j) == '0') // Dead
                //     if (count > birthLimit)
                //        caveMatrix_(i, j) = '1';

                if (caveMatrix_(i, j) == '1') // Living
                    if (count < deathLimit)
                        caveMatrix_(i, j) = '0';

                if (caveMatrix_(i, j) == '0') // Dead
                    if (count > birthLimit)
                       caveMatrix_(i, j) = '1';
           }
        }

        Observable::notifyUpdate();

        return {true, ""};  
    }

    int Cave::countLivingNeighbors(S21Matrix<char> field, int row, int col){
        int rows = caveMatrix_.GetRows();
        int cols = caveMatrix_.GetCols();

        int count = 0;

        for(int x = -1 ; x <= 1 ; x++){
            for(int y = -1 ; y <= 1 ; y++){
                if(x == 0 && y == 0)
                    continue;

                Point<int> point = {col + x, row + y};

                if(point.col < 0 || point.row < 0 || 
                   point.col >= cols || point.row >= rows){
                    count++;
                }else
                    count += caveMatrix_(point.row, point.col) == '1' ? 1 : 0;
            }
        }

        return count;
    }

    std::vector<Rect> Cave::get(float width, float height){
        float rows = caveMatrix_.GetRows();
        float cols = caveMatrix_.GetCols();

        std::vector<Rect> lines;

        if (!rows || !cols)
            return lines;

        lines.reserve(rows * cols + 4);

        float baseCellSize = std::min(width / rows, height / cols);

        // Calculate scaling factors to maintain aspect ratio within each cell
        float scaleFactorX = width / (baseCellSize * cols);
        float scaleFactorY = height / (baseCellSize * rows);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (caveMatrix_(i, j) == '1'){
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
}