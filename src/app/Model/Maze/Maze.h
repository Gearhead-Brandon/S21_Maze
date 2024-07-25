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
    
    class Maze : public Observable{
        
        S21Matrix<char> verticalMatrix_;
        S21Matrix<char> horizontalMatrix_;
        PathFinder* pathFinder_;

    public:

        Maze();
        ~Maze();

        OpResult load(const std::string &path);
        OpResult generate(int rows, int cols);
        std::vector<Line> get(float width, float height);

        PathRenderConfig getPath(float width, float height);
        void clearPath();

        void setStartPosition(Point<float> p, float width, float height);
        void setEndPosition(Point<float> p, float widht, float height);
        
    private:

        void loadMatrixToFile(const S21Matrix<char> &matrix, std::ofstream& file, bool eof);
        void save();
        void loadMazeForPathFinder();
    };
}

#endif