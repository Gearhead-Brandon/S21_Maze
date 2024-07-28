#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include "../../S21Matrix/S21Matrix.h"
#include "../../../Common/Structures/OpResult/OpResult.h"

namespace s21{

    class MazeGenerator {
        
        S21Matrix<char>& verticalMatrix_;
        S21Matrix<char>& horizontalMatrix_;
        std::vector<int> mazeLine_;
        int setCounter_;
        int rows_;
        int cols_;

    public:

        MazeGenerator(S21Matrix<char>& verticalMatrix
                     , S21Matrix<char>& horizontalMatrix
                     , int rows, int cols);

        OpResult generate();

    private:

        char random();

        void assignUniqueSets();

        void setVerticalWalls(int row);
        void mergeSet(int index);

        void setHorizontalWalls(int row);
        int countUniqueSet(int num);
        //void horizontalWallsCheck(int row);
        int countHorizontalWalls(int num, int row);
        
        void updateLine(int row);

        void setEndLine();
        void endLineCheck();
    };
}

#endif