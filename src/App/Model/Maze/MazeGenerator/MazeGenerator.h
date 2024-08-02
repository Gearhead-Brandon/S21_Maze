/**
 * @file MazeGenerator.h
 * @brief Header file describing the class MazeGenerator
 */

#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <vector>
#include "../../S21Matrix/S21Matrix.h"
#include "../../../Common/Structures/OpResult/OpResult.h"

namespace s21{

    /**
     * @brief Maze generator
     */
    class MazeGenerator {
        
        //! Reference to the matrix of vertical walls
        S21Matrix<char>& verticalMatrix_;

        //! Reference to the matrix of horizontal walls
        S21Matrix<char>& horizontalMatrix_;

        //! Current line of the maze
        std::vector<int> mazeLine_;

        //! Set counter
        int setCounter_;

        //! Number of rows
        int rows_;

        //! Number of columns
        int cols_;

    public:

        /**
         * @brief Parametrized constructor
         * @param verticalMatrix - reference to the matrix of vertical walls
         * @param horizontalMatrix - reference to the matrix of horizontal walls
         * @param rows - number of rows
         * @param cols - number of columns
         */
        MazeGenerator(S21Matrix<char>& verticalMatrix
                     , S21Matrix<char>& horizontalMatrix
                     , int rows, int cols);

        /**
         * @brief Generate maze 
         * @return Operation result
         */
        OpResult generate();

    private:

        /**
         * @brief Random number generator
         * @return Random number
         */
        char random();

        /**
         * @brief Assign unique sets to the current line of the maze
         */
        void assignUniqueSets();

        /**
         * @brief Set vertical walls for the current row
         * @param row - current row
         */
        void setVerticalWalls(int row);

        /**
         * @brief Merge sets in the current line
         * @param index - index of the current cell
         */
        void mergeSet(int index);

        /**
         * @brief Set horizontal walls for the current row
         * @param row - current row
         */
        void setHorizontalWalls(int row);

        /**
         * @brief Count unique sets in the current line
         * @param num - number of the current line
         * @return Count of unique sets
         */
        int countUniqueSet(int num);

        /**
         * @brief Count horizontal walls in the current line
         * @param num - number of the current line
         * @param row - current row
         * @return Count of horizontal walls
         */
        int countHorizontalWalls(int num, int row);
        
        /**
         * @brief Update line of the maze
         * @param row - current row
         */
        void updateLine(int row);

        /**
         * @brief Set end line
         */
        void setEndLine();

        /**
         * @brief End line check
         */
        void endLineCheck();
    };
}

#endif