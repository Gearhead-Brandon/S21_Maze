/**
 * @file Model.h
 * @brief Header file describing the class Model
 */

#ifndef MODEL_H
#define MODEL_H

#include "Maze/Maze.h"
#include "Cave/Cave.h"
#include "../Common/Enum/AreaType.h"

namespace s21{

    /**
     * @class Model of the application
     */
    class Model {
        
        //! Pointer to the maze
        Maze* maze_;

        //! Pointer to the cave
        Cave* cave_;

    public:

        /**
         * @brief Default constructor
         */
        Model();

        /**
         * @brief Default destructor
         */
        ~Model();

        /**
         * @brief Add observer
         * @param observer - pointer to the observer
         * @param type - type of the area
         */
        void addObserver(IObserver* observer, AreaType type);

        /**
         * @brief Load maze
         * @param path - path to the file
         * @return Operation result
         */
        OpResult loadMaze(const std::string &path);

        /**
         * @brief Generate maze
         * @param rows - number of rows
         * @param cols - number of columns
         * @return Operation result
         */
        OpResult generateMaze(int rows, int cols);

        /**
         * @brief Get maze
         * @param width - width of the maze
         * @param height - height of the maze
         * @return Vector of walls
         */
        std::vector<Line> getMaze(float width, float height);

        /**
         * @brief Load cave
         * @param path - path to the file
         * @return Operation result
         */
        OpResult loadCave(const std::string &path);

        /**
         * @brief Generate cave
         * @param rows - number of rows
         * @param cols - number of columns
         * @param initChance - chance of initial living cells
         * @return Operation result
         */
        OpResult generateCave(int rows, int cols, int initChance);

        /**
         * @brief Transform cave
         * @param full - full or not
         * @param birthLimit - birth limit
         * @param deathLimit - death limit
         * @param time - time in milliseconds
         * @return Operation result
         */
        OpResult transformCave(bool full, int birthLimit, int deathLimit, int time);
        
        /**
         * @brief Get cave
         * @param width - width of the cave
         * @param height - height of the cave
         * @return Vector of cave cells
         */
        std::vector<Rect> getCave(float width, float height) const;

        /**
         * @brief Get path
         * @param width - width of the area
         * @param height - height of the area
         * @return PathRenderConfig
         */
        PathRenderConfig getPath(float width, float height);

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
         * @brief Path finding through the Q-Learning algorithm
         * @param start - start position
         * @param goal - goal position
         * @return Operation result
         */
        OpResult QPathFinding(Point<int> start, Point<int> goal);

        /**
         * @brief Clear the path
         */
        void clearPath();
    };
}

#endif