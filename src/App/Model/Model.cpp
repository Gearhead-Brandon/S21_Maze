/**
 * @file Model.cpp
 * @brief Implementation of the class Model
 */

#include "Model.h"

namespace s21{

    /**
     * @brief Default constructor
     */
    Model::Model() : maze_(new Maze), cave_(new Cave){}

    /**
     * @brief Default destructor
     */
    Model::~Model(){
        delete maze_;
        delete cave_;
    }

    /**
     * @brief Add observer
     * @param observer - pointer to the observer
     * @param type - type of the area
     */
    void Model::addObserver(IObserver* observer, AreaType type){
        if(type == AreaType::Maze)
            maze_->addObserver(observer);
        else if(type == AreaType::Cave)
            cave_->addObserver(observer);
    }

    /**
     * @brief Load maze
     * @param path - path to the file
     * @return Operation result
     */
    OpResult Model::loadMaze(const std::string& path){
        return maze_->load(path);
    }

    /**
     * @brief Generate maze
     * @param rows - number of rows
     * @param cols - number of columns
     * @return Operation result
     */
    OpResult Model::generateMaze(int rows, int cols){
        return maze_->generate(rows, cols);
    }

    /**
     * @brief Transform cave
     * @param full - full or not
     * @param birthLimit - birth limit
     * @param deathLimit - death limit
     * @param time - time in milliseconds
     * @return Operation result
     */
    OpResult Model::transformCave(bool full, int birthLimit, int deathLimit, int time){
        return cave_->transform(full, birthLimit, deathLimit, time);
    }

    /**
     * @brief Load cave
     * @param path - path to the file
     * @return Operation result
     */
    OpResult Model::loadCave(const std::string &path){
        return cave_->load(path);
    }

    /**
     * @brief Generate cave
     * @param rows - number of rows
     * @param cols - number of columns
     * @param initChance - chance of initial living cells
     * @return Operation result
     */
    OpResult Model::generateCave(int rows, int cols, int initChance){
        return cave_->generate(rows, cols, initChance);
    }

    /**
     * @brief Get maze
     * @param width - width of the maze
     * @param height - height of the maze
     * @return Vector of walls
     */
    std::vector<Line> Model::getMaze(float width, float height){
        return maze_->get(width, height);
    }

    /**
     * @brief Get path
     * @param width - width of the area
     * @param height - height of the area
     * @return PathRenderConfig
     */
    PathRenderConfig Model::getPath(float width, float height){
        return maze_->getPath(width, height);
    }

    /**
     * @brief Get cave
     * @param width - width of the cave
     * @param height - height of the cave
     * @return Vector of cave cells
     */
    std::vector<Rect> Model::getCave(float width, float height) const{
        return cave_->get(width, height);
    }

    /**
     * @brief Path finding through the Q-Learning algorithm
     * @param start - start position
     * @param goal - goal position
     * @return Operation result
     */
    OpResult Model::QPathFinding(Point<int> start, Point<int> end){
        return maze_->QPathFinding(start, end);
    }

    /**
     * @brief Clear the path
     */
    void Model::clearPath(){
        maze_->clearPath();
    }

    /**
     * @brief Set the start position of the path
     * @param p - start position
     * @param width - width of the area
     * @param height - height of the area
     */
    void Model::setStartPosition(Point<float> p, float width, float height){
        maze_->setStartPosition(p, width, height);
    }

    /**
     * @brief Set the end position of the path
     * @param p - end position
     * @param width - width of the area
     * @param height - height of the area
     */
    void Model::setEndPosition(Point<float> p, float width, float height){
        maze_->setEndPosition(p, width, height);
    }
}