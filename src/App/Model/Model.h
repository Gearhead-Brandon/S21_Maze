#ifndef MODEL_H
#define MODEL_H

#include "Maze/Maze.h"
#include "Cave/Cave.h"
#include "../Common/Enum/AreaType.h"

namespace s21{

    class Model {//: public Observable{

        Maze* maze_;
        Cave* cave_;

    public:
        Model();
        ~Model();

        void addObserver(IObserver* observer, AreaType type);

        OpResult loadMaze(const std::string &path);
        OpResult generateMaze(int rows, int cols);
        std::vector<Line> getMaze(float width, float height);

        OpResult loadCave(const std::string &path);
        OpResult generateCave(int rows, int cols, int initChance);
        //OpResult transformCave(int birthLimit, int deathLimit);
        OpResult transformCave(bool full, int birthLimit, int deathLimit, int time);
        std::vector<Rect> getCave(float width, float height);

        PathRenderConfig getPath(float width, float height);

        void setStartPosition(Point<float> p, float width, float height);
        void setEndPosition(Point<float> p, float widht, float height);

        OpResult QPathFinding(Point<int> start, Point<int> goal);

        void clearPath();
    };
}

#endif