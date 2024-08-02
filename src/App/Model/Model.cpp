#include "Model.h"

namespace s21{
    Model::Model() : maze_(new Maze), cave_(new Cave){}

    Model::~Model(){
        delete maze_;
        delete cave_;
    }

    void Model::addObserver(IObserver* observer, AreaType type){
        if(type == AreaType::Maze)
            maze_->addObserver(observer);
        else if(type == AreaType::Cave)
            cave_->addObserver(observer);
    }

    OpResult Model::loadMaze(const std::string& path){
        return maze_->load(path);
    }

    OpResult Model::generateMaze(int rows, int cols){
        return maze_->generate(rows, cols);
    }

    OpResult Model::transformCave(bool full, int birthLimit, int deathLimit, int time){
        return cave_->transform(full, birthLimit, deathLimit, time);
    }

    OpResult Model::loadCave(const std::string &path){
        return cave_->load(path);
    }

    OpResult Model::generateCave(int rows, int cols, int initChance){
        return cave_->generate(rows, cols, initChance);
    }

    std::vector<Line> Model::getMaze(float width, float height){
        return maze_->get(width, height);
    }

    PathRenderConfig Model::getPath(float width, float height){
        return maze_->getPath(width, height);
    }

    std::vector<Rect> Model::getCave(float width, float height){
        return cave_->get(width, height);
    }

    OpResult Model::QPathFinding(Point<int> start, Point<int> end){
        return maze_->QPathFinding(start, end);
    }

    void Model::clearPath(){
        maze_->clearPath();
    }

    void Model::setStartPosition(Point<float> p, float width, float height){
        maze_->setStartPosition(p, width, height);
    }

    void Model::setEndPosition(Point<float> p, float width, float height){
        maze_->setEndPosition(p, width, height);
    }
}