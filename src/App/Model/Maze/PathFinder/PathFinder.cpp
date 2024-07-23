#include "PathFinder.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <set> 

namespace s21{

    PathFinder::PathFinder() : start_({-1, -1}), end_({-1, -1}), path_(){}

    void PathFinder::setMaze(S21Matrix<char>&& maze){
        reset();
        maze_ = std::move(maze);
    }

    void PathFinder::setStartPosition(Point<float> start, float wRatio, float hRatio){
        if(start.col > 0.0f  && start.row > 0.0f && start.col != start_.col && start.row != start_.row){
            // int rowIndex = floor(start_.y / (height / rows));
            // int colIndex = floor(start_.x / (width / cols));

            float x = start.col;
            float y = start.row;

            int rowIndex = y / hRatio;
            int colIndex = x / wRatio;

            Point<int> copy = start_;

            start_ = {colIndex, rowIndex};

            try{
                if(end_.col > -1 && end_.row > -1)
                    findPathAStar();
            }catch(const OpResult& e){
                start_ = copy;
                throw e;
            }
        }
    }

    void PathFinder::setEndPosition(Point<float> end, float wRatio, float hRatio){
        if(end.col > 0  && end.row > 0 && end.col != end_.col && end.row != end_.row){
            // int rowIndex = floor(end_.y / (height / rows));
            // int colIndex = floor(end_.x / (width / cols))

            float x = end.col;
            float y = end.row;

            int rowIndex = y / hRatio;
            int colIndex = x / wRatio;

            Point<int> copy = end_;

            end_ = {colIndex, rowIndex};

            try{
                if(start_.col > -1 && start_.row > -1)
                    findPathAStar();
            }catch(const OpResult& e){
                end_ = copy;
                throw e;
            }
        }
    }

    void PathFinder::reset(){
        start_ = {-1, -1};
        end_ = {-1, -1};
        path_.clear();
    }

    void PathFinder::setPointToPath(Point<int> el, PathRenderConfig& config, Point<float> areaSize){
        if(el.row > -1 && el.col > -1){
            int width = areaSize.col;
            int height = areaSize.row;

            int rows = maze_.GetRows() / 2;
            int cols = maze_.GetCols() / 2;

            // Рассчитать базовый размер клетки
            float baseCellSize = std::min(width / cols, height / rows);
            float squareSize = baseCellSize / 4;  // Размер квадрата начальной точки

            // Рассчитать масштабирование для каждого измерения
            float scaleFactorX = width / (baseCellSize * cols);
            float scaleFactorY = height / (baseCellSize * rows);

            int colIndex = el.col;
            int rowIndex = el.row;

            // Рассчитать центральные координаты клетки с центрированием
            float centerX = (colIndex + 0.5f) * baseCellSize * scaleFactorX;
            float centerY = (rowIndex + 0.5f) * baseCellSize * scaleFactorY;

            // Создать квадрат начальной точки в центре клетки
            config.points_.push_back({centerX - squareSize / 2, centerY - squareSize / 2,
                                        squareSize, squareSize});
        }
    }

    PathRenderConfig PathFinder::get(Point<float> areaSize){
        int rows = maze_.GetRows() / 2;
        int cols = maze_.GetCols() / 2;

        if((start_.col >= cols || start_.row >= rows) || (end_.col >= cols || end_.row >= rows))
            return {};

        PathRenderConfig config;

        setPointToPath(start_, config, areaSize);
        setPointToPath(end_, config, areaSize);

        if(start_.col > -1 && start_.row > -1 && end_.col > -1 && end_.row > -1)
            fillPath(config, areaSize);

        return config;
    }

    void PathFinder::fillPath(
        PathRenderConfig& config,
        Point<float> areaSize){

        if(!path_.size()) 
            return;
        
        int rows = maze_.GetRows() / 2;
        int cols = maze_.GetCols() / 2;

        int width = areaSize.col;
        int height = areaSize.row;

        float baseCellSize = std::min(width / cols, height / rows);

        // Calculate scaling factors to maintain aspect ratio within each cell
        float scaleFactorX = width / (baseCellSize * cols);
        float scaleFactorY = height / (baseCellSize * rows);

        // Loop through path elements
        for (size_t i = 0; i < path_.size() - 1; ++i) {
            const Point<int> current = path_[i];
            const Point<int> next = path_[i + 1];

            // Calculate center coordinates of current and next cells
            float currentCenterX = (current.col / 2 + 0.5f) * baseCellSize * scaleFactorX;
            float currentCenterY = (current.row / 2 + 0.5f) * baseCellSize * scaleFactorY;

            float nextCenterX = (next.col / 2 + 0.5f) * baseCellSize * scaleFactorX;
            float nextCenterY = (next.row / 2 + 0.5f) * baseCellSize * scaleFactorY;

            // Draw line connecting centers
            config.path_.push_back({currentCenterX, currentCenterY, nextCenterX, nextCenterY});
        }
    }


    bool PathFinder::isValid(int x, int y) {
        const int rows = maze_.GetRows();
        const int cols = maze_.GetCols();

        if((x >= 0 && x < cols) && (y >= 0 && y < rows))
            return maze_(y, x) == '0';

        return false;
    }

    int PathFinder::calculateG(Point<int> current, Point<int> next) {
        // Проверка, является ли переход диагональным
        bool isDiagonal = (current.col != next.col) && (current.row != next.row);

        // Стоимость горизонтального/вертикального перехода
        int straightCost = 1;

        // Стоимость диагонального перехода (может быть больше)
        //int diagonalCost = isDiagonal ? 1.4142 : 2;

        // Расчет стоимости перехода
        int g = 0;
        if (current.col == next.col) {
            g = straightCost * std::abs(current.row - next.row);
        } else if (current.row == next.row) 
            g = straightCost * std::abs(current.col - next.col);
        // } else {
        //     g = diagonalCost * std::min(std::abs(current.col - next.col), std::abs(current.row - next.row));
        // }

        return g;
    }

    int PathFinder::calculateHeuristic(Point<int> point, Point<int> goal) {
        // Расстояние по Манхэттэну
        int dx = std::abs(point.col - goal.col);
        int dy = std::abs(point.row - goal.row);

        return dx + dy;
    }

    void PathFinder::findPathAStar(){
        Point<int> start = start_;
        Point<int> goal = end_;

        // Умножение на 2 для учета "расширенной" размерности (стены занимают 2 клетки)
        start.col *= 2;
        start.row *= 2;
        goal.col *= 2;
        goal.row *= 2;

        // Очередь приоритетов для узлов (пара: f-оценка, точка)
        std::priority_queue<std::pair<int, Point<int>>, std::vector<std::pair<int, Point<int>>>, 
                            std::greater<std::pair<int, Point<int>>>> pq;

        // Множество посещенных точек
        std::set<Point<int>> visited;

        // Словарь для хранения родительских узлов
        std::map<Point<int>, Point<int>> parent;

        // Начальная f-оценка (g = 0, h = эвристика)
        int f_start = calculateHeuristic(start, goal);
        pq.push({f_start, start});

        visited.insert(start);

        int dx_order[] = {-1, 0, 1, 0};
        int dy_order[] = {0, -1, 0, 1};

        //std::vector<Point<int>> path;

        while (!pq.empty()) {
            Point<int> current = pq.top().second;
            pq.pop();

            if (current == goal) {
                // std::cout << "ПУТЬ НАЙДЕН" << std::endl;

                // S21Matrix<char> copy = maze_;
                // for(int i = 0; i < copy.GetRows() ; i++)
                //     for(int j = 0; j < copy.GetCols() ; j++)
                //         for(auto el : path)
                //             if(i == el.row && j == el.col) copy(i, j) = '2';

                // std::cout << std::endl;
                // for(int i = 0; i < copy.GetRows() ; i++){
                //     for(int j = 0; j < copy.GetCols() ; j++){
                //         if(copy(i,j) == '1')
                //             std::cout << "* ";
                //         else if(copy(i,j) == '2')
                //             std::cout << "X ";
                //         else if(copy(i,j) == '0')
                //             std::cout << "@ ";
                //     }
                //     std::cout << std::endl;
                // }
                
                reconstructPath(parent, start, goal);
                return;
            }

            for (int i = 0; i < 4; ++i) {
                int dx = dx_order[i];
                int dy = dy_order[i];

                Point<int> next = {current.col + dx, current.row + dy};

                if (isValid(next.col, next.row) && !visited.count(next)) {
                    int g_new = calculateG(current, next) + calculateG(start, current);
                    int h_new = calculateHeuristic(next, goal);
                    int f_new = g_new + h_new;

                    pq.push({f_new, next});
                    visited.insert(next);
                    parent[next] = current;
                }
            }
        }
        
        throw OpResult(false, "Path not found. Probably the labyrinth has isolated study areas");
    }

    void PathFinder::reconstructPath(
        std::map<Point<int>, Point<int>>& parent,
        const Point<int>& start, 
        const Point<int>& end){
        
        path_.clear();

        Point<int> current = end;

        while (current != start) {
            if (!parent.count(current))
                return;  // No path found (e.g., unreachable endpoint)

            path_.push_back(current);
            current = parent.at(current);
        }

        path_.push_back(start);  // Add start point to the path

        //std::reverse(path.begin(), path.end());  // Reverse for correct order

        // S21Matrix<char> copy = maze_;

        // for(int i = 0; i < copy.GetRows() ; i++)
        //     for(int j = 0; j < copy.GetCols() ; j++)
        //         for(auto el : path_)
        //             if(i == el.row && j == el.col) copy(i, j) = '2';

        // std::cout << std::endl;
        // for(int i = 0; i < copy.GetRows() ; i++){
        //     for(int j = 0; j < copy.GetCols() ; j++){
        //         if(copy(i,j) == '1')
        //             std::cout << "* ";
        //         else if(copy(i,j) == '2')
        //             std::cout << "X ";
        //         else if(copy(i,j) == '0')
        //             std::cout << "@ ";
        //     }
        //     std::cout << std::endl;
        // }
    }
}

// bool PathFinder::isValid(const S21Matrix<char>& maze2, int x, int y) {
//         const int rows = maze_.GetRows();
//         const int cols = maze_.GetCols();

//         if((x >= 0 && x < cols) && (y >= 0 && y < rows)){
//             // bool r = false;

//             // if(maze(y,x) == '0')
//             //     return true;

//             // return false;
//             return maze_(y, x) == '0';
//         }

//         return false;

//         // if ((x >= 0 && x < rows) && (y >= 0 && y < cols)) {
//         //     bool r = false;

//         //     // Check if it's a valid path character (e.g., '0') and allow only horizontal or vertical movements
//         //     if (maze(y, x) == '0' &&
//         //         ((x > 0 && maze(y, x - 1) != '1') ||        // Check left cell
//         //         (x < cols - 1 && maze(y, x + 1) != '1') ||  // Check right cell
//         //         (y > 0 && maze(y - 1, x) != '1') ||         // Check top cell
//         //         (y < rows - 1 && maze(y + 1, x) != '1'))) {  // Check bottom cell
//         //         r = true;
//         //     }
//         //}

//         //return false;

//         //return (x >= 0 && x < rows) && (y >= 0 && y < cols) && maze(x,y) == '0';
//     }

//     void PathFinder::findPathBFS(S21Matrix<char>& maze2){
//         Point<int> start = start_;
//         Point<int> goal = end_;

//         start.col *= 2;
//         start.row *= 2;
//         goal.col *= 2;
//         goal.row *= 2;

//         std::queue<Point<int>> q;
//         q.push(start);

//         std::set<Point<int>> visited;
//         visited.insert(start);

//         //std::vector<Point<int>> path2;

//         std::map<Point<int>, Point<int>> parent;

//         // std::cout << "Start = " << start_.row << " " << start_.col << std::endl;
//         // std::cout << "IStart = " << start.row << " " << start.col << std::endl;
//         // std::cout << "End = " << end_.row << " " << end_.col << std::endl;
//         // std::cout << "IEnd = " << end.row << " " << end.col << std::endl;

//         // maze.PrintMatrix();
//         // std::cout << std::endl;

//         int dx_order[] = {-1, 0, 1, 0};
//         int dy_order[] = {0, -1, 0, 1};

//         while(!q.empty()){
//             Point<int> current = q.front();
//             q.pop();

//             if(current == goal){
//                 std::cout << "FOUND" << std::endl;
//                 reconstructPath(parent, start, goal);
//                 return;
//             }

//             for (int i = 0; i < 4; ++i) {  // Loop through directions in order
//                 int dx = dx_order[i];
//                 int dy = dy_order[i];

//                 Point<int> next = {current.col + dx, current.row + dy};

//                 if (isValid(maze_, next.col, next.row) && !visited.count(next)){
//                     q.push(next);
//                     visited.insert(next);
//                     //path_.push_back(next);
//                     parent[next] = current;
//                 }
//             }
//         }

//         std::cout << "<<< NOT FOUND >>>" << std::endl;
//         //return {};
//     }