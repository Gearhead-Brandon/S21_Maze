#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../../../Common/Structures/PathRenderConfig/PathRenderConfig.h"
#include "../../../Common/Structures/OpResult/OpResult.h"
#include "../../../Common/Structures/Primitives/Point.h"
#include "../../S21Matrix/S21Matrix.h"
#include "Components/QActions.h"
#include <random>
#include <cmath>
#include <map> 

namespace s21{
    class PathFinder{

        Point<int> start_;
        Point<int> end_;
        std::vector<Point<int>> path_;
        S21Matrix<char> maze_;

        using QTable = std::vector<std::vector<QActions>>;

    public:
        PathFinder();
        ~PathFinder() = default;

        void setStartPosition(Point<float> start, float wRatio, float hRatio);
        void setEndPosition(Point<float> end, float wRatio, float hRatio);

        PathRenderConfig get(Point<float> areaSize);

        void setMaze(S21Matrix<char>&& maze);

        OpResult QPathFinding(Point<int> start, Point<int> goal);

        void reset();
    
    private:
        void setPointToPath(Point<int> el, PathRenderConfig& config, Point<float> areaSize);
        
        void fillPath(PathRenderConfig& config, Point<float> areaSize);

        int calculateG(Point<int> current, Point<int> next);

        int calculateHeuristic(Point<int> point, Point<int> goal);

        bool isNotWall(int x, int y);

        void findPathAStar();

        void reconstructPath(std::map<Point<int>, Point<int>>& parent,
                             const Point<int>& start, const Point<int>& end);
    
        Action selectAction(const QTable& qTable, Point<int> currentPos, float epsilon);

        Action selectMaxAction(const QTable& qTable, Point<int> currentPos);

        Point<int> getNextPoint(Point<int> current, Action action);

        float getReward(Point<int> current, Point<int>& next, Point<int> goal, bool& done);
    
        void updateQTable(QTable& qTable, Point<int> currentState, Action action, Point<int> next, float reward, float alpha, float gamma);

        int getEpisodesCount();

        OpResult buildQPath(const QTable& qTable);

        void findPath(Point<int>& first, Point<int> second, Point<int> copy);
    };
}
#endif