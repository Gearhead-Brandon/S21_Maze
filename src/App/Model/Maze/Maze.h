/**
 * @file Maze.h
 * @brief Header file describing the class Maze
 */

#ifndef MAZE_H
#define MAZE_H

#include "../S21Matrix/S21Matrix.h"
#include "../../Common/Structures/OpResult/OpResult.h"
#include "../../Common/Structures/Primitives/Line.h"
#include "../../Common/Structures/Observer/Observable/Observable.h"
#include "MazeGenerator/MazeGenerator.h"
#include "PathFinder/PathFinder.h"
#include <vector>

namespace s21{
    
    /**
     * @brief Class describing the maze
     * @details Model implements the interface Observable
     */
    class Maze : public Observable{
        
        //! Matrix of vertical walls
        S21Matrix<char> verticalMatrix_;
        
        //! Matrix of horizontal walls
        S21Matrix<char> horizontalMatrix_;

        //! Path finder
        PathFinder* pathFinder_;

    public:

        /**
         * @brief Default constructor
         */
        Maze();

        /**
         * @brief Default destructor
         */
        ~Maze();

        /**
         * @brief Load maze from file
         * @param path - path to the file
         * @return Operation result
         */
        OpResult load(const std::string &path);

        /**
         * @brief Generate maze
         * @param rows - number of rows
         * @param cols - number of columns
         * @return Operation result
         */
        OpResult generate(int rows, int cols);

        /**
         * @brief Get the path
         * @param width - width of the area
         * @param height - height of the area
         * @return Vector of walls
         */
        std::vector<Line> get(float width, float height);

        /**
         * @brief Get the maze path
         */
        PathRenderConfig getPath(float width, float height);

        /**
         * @brief Clear the path
         */
        void clearPath();

        /**
         * @brief Set the start position of the path
         * @param p - start position
         * @param width - width of the area
         * @param height - height of the area
         */
        void setStartPosition(Point<float> p, float width, float height);

        /**
         * @brief Set the end position of the path
         * @param p - end position
         * @param width - width of the area
         * @param height - height of the area
         */
        void setEndPosition(Point<float> p, float widht, float height);
        
        /**
         * @brief Find the path through the Q-Learning algorithm
         * @param start - start position
         * @param end - end position
         * @return Operation result
         */
        OpResult QPathFinding(Point<int> start, Point<int> end);

    private:

        /**
         * @brief Save the matrix to file
         * @param matrix - matrix
         * @param path - path to the file
         * @param eof - end of file
         */
        void loadMatrixToFile(const S21Matrix<char> &matrix, std::ofstream& file, bool eof);

        /**
         * @brief Save the maze to file
         */
        void save();

        /**
         * @brief Clear the maze
         */
        void clear();

        /**
         * @brief Load maze for path finder
         */
        void loadMazeForPathFinder();
    };
}

#endif