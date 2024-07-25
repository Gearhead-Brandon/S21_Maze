#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../../../Common/Structures/Primitives/Point.h"
#include "../../../Common/Structures/PathRenderConfig/PathRenderConfig.h"
#include "../../../Common/Structures/OpResult/OpResult.h"
#include "../../S21Matrix/S21Matrix.h"
#include "Components/StateAction.h"
#include <map> 

namespace s21{
    class PathFinder{

        Point<int> start_;
        Point<int> end_;
        std::vector<Point<int>> path_;
        S21Matrix<char> maze_;

    public:
        PathFinder();
        ~PathFinder() = default;

        void setStartPosition(Point<float> start, float wRatio, float hRatio);
        void setEndPosition(Point<float> end, float wRatio, float hRatio);

        PathRenderConfig get(Point<float> areaSize);

        void setMaze(S21Matrix<char>&& maze);

        void QPathFinding(Point<int> start, Point<int> end);

        void reset();
    
    private:
        //void reset();

        void setPointToPath(Point<int> el, PathRenderConfig& config, Point<float> areaSize);
        
        void fillPath(PathRenderConfig& config, Point<float> areaSize);

        int calculateG(Point<int> current, Point<int> next);

        int calculateHeuristic(Point<int> point, Point<int> goal);

        bool isValid(int x, int y);

        void findPathAStar();

        void reconstructPath(std::map<Point<int>, Point<int>>& parent,
                             const Point<int>& start, const Point<int>& end);
    };
}
#endif