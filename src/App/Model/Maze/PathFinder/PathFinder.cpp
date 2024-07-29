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

        // Мап для хранения родительских узлов
        std::map<Point<int>, Point<int>> parent;

        // Начальная f-оценка (g = 0, h = эвристика)
        int f_start = calculateHeuristic(start, goal);
        pq.push({f_start, start});

        visited.insert(start);

        int dx_order[] = {-1, 0, 1, 0};
        int dy_order[] = {0, -1, 0, 1};

        while (!pq.empty()) {
            Point<int> current = pq.top().second;
            pq.pop();

            if (current == goal) {
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
        const Point<int>& end
    ){  
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

    Action PathFinder::selectMaxAction(const QTable& qTable, Point<int> currentPos){
        const auto& state = qTable[currentPos.row][currentPos.col];
        auto max = std::max_element(state.qValues.begin(), state.qValues.end());
        return static_cast<Action>(std::distance(state.qValues.begin(), max));
    }

    Action PathFinder::selectAction(const QTable& qTable, Point<int> currentPos, float epsilon){
        const auto& state = qTable[currentPos.row][currentPos.col];

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0, 1.0);

        float r = dis(gen);

        if(r < epsilon){
            std::uniform_int_distribution<int> action_dis(0, state.qValues.size() - 1);
            return static_cast<Action>(action_dis(gen));
        }else{
            // auto max = std::max_element(state.qValues.begin(), state.qValues.end());
            // return static_cast<Action>(std::distance(state.qValues.begin(), max));
            return selectMaxAction(qTable, currentPos);
        }
    }

    Point<int> PathFinder::getNextPoint(Point<int> current, Action action){
        Point<int> next{current.col, current.row};
        switch(action){
            case Action::LEFT: 
                next.col--;
                break;
            case Action::UP: 
                next.row--;
                break;
            case Action::RIGHT:
                next.col++;
                break;
            case Action::DOWN:
                next.row++;
                break;
        }

        return next;
    }

    float PathFinder::getReward(Point<int> current, Point<int>& next, Point<int> goal, bool& done){
        if(next == goal){
            done = true;
            return 10.0f;
        }else if(!isValid(next.col, next.row)){
            done = true;
            next = current;
            return -10.0f;
        }else
            return -0.1f;
    }

    void PathFinder::updateQTable(
        QTable& qTable, Point<int> currentState, 
        Action action, Point<int> next, 
        float reward, float alpha, float gamma){

        auto& state = qTable[currentState.row][currentState.col];
        int index = static_cast<int>(action);

        auto& nextState = qTable[next.row][next.col];
        float maxQNext = *std::max_element(nextState.qValues.begin(), nextState.qValues.end()); 

        // state.qValues[index] = state.qValues[index] + alpha * (reward + gamma * maxQNext - state.qValues[index]);
        float tg_target = reward + gamma * maxQNext;
        float tg_error = tg_target - state.qValues[index];
        qTable[currentState.row][currentState.col].qValues[index] += alpha * tg_error;
        //state.qValues[index] = (1-alpha) * state.qValues[index] + alpha * (reward + gamma * maxQNext - state.qValues[index]);
    }

    int PathFinder::getEpisodesCount(){
        int rows = maze_.GetRows() / 2;
        int cols = maze_.GetCols() / 2;

        if(cols > rows)
            rows = cols;

        if(rows <= 30)
            return static_cast<float>(rows) * 1.55f * 100.0f;

        if(rows > 40)
            return rows * 2 * 100 + 500;

        return rows * 2 * 100;
    }

    void PathFinder::QPathFinding(Point<int> start, Point<int> goal){
        int rows = maze_.GetRows() / 2;
        int cols = maze_.GetCols() / 2;
        
        if( start.col < 0 || start.col >= cols || start.row < 0 || start.row >= rows ||
            goal.col < 0  || goal.col >= cols  || goal.row < 0  || goal.row >= rows){
            std::cout << "Incorrect maze size" << std::endl;
            return;
        }

        QTable qTable(maze_.GetRows(), std::vector<QActions>(maze_.GetCols(), QActions()));
        
        start_ = start;
        end_ = goal;

        start.col *= 2;
        start.row *= 2;
        goal.col  *= 2;
        goal.row  *= 2;

        float alpha = 0.9f;
        float gamma = 0.98f;

        float e_initial = 1.0f;
        float decay_rate = 0.01f;
        float epsilon = 0.0f;

        //int numEpisodes = 10'000; // 11000
        int numEpisodes = getEpisodesCount();

        S21Matrix<char> copy = maze_;

        std::cout << std::endl;
        for(int i = 0; i < copy.GetRows() ; i++){
            for(int j = 0; j < copy.GetCols() ; j++){
                if(copy(i,j) == '1')
                    std::cout << "* ";
                else if(copy(i,j) == '2')
                    std::cout << "X ";
                else if(copy(i,j) == '0')
                    std::cout << "@ ";
            }
            std::cout << std::endl;
        }

        std::cout << "COUNT EPISODES = " << numEpisodes << std::endl;

        for(int episode = 0; episode < numEpisodes; episode++){
            Point<int> currentState = start;
            
            bool done = false;

            while(!done){
                
                Action action = selectAction(qTable, currentState, epsilon);

                Point<int> next = getNextPoint(currentState, action);

                float reward = getReward(currentState, next, goal, done);

                updateQTable(qTable, currentState, action, next, reward, alpha, gamma);

                currentState = next;
            }

            epsilon = e_initial * exp(-decay_rate * episode );
            //std::cout << "episode = " << episode << " | counter = " << counter << std::endl;
        }

        buildQPath(qTable);
    }

    void PathFinder::buildQPath(const QTable& qTable){
        std::cout << "buildQPath" << std::endl;
        int count = 0;

        // std::cout << "START = " << start_.row << " " << start_.col << std::endl;
        // std::cout << "END_ = " << end_.row << " " << end_.col << std::endl;
        // std::cout << std::endl;

        // for(int i = 0; i < maze_.GetRows(); i++)
        //     for(int j = 0; j < maze_.GetCols(); j++){
        //         std::cout << i << " " << j << std::endl;
        //         std::cout << "L: " << qTable[i][j].qValues[0] << " U: " << qTable[i][j].qValues[1] << " R: " << qTable[i][j].qValues[2] << " D: " << qTable[i][j].qValues[3] << std::endl;
        //     }

        Point<int> current = start_;
        Point<int> end = end_;

        end.col *= 2;
        end.row *= 2;

        std::cout << "START = " << start_.row*2 << " " << start_.col*2 << std::endl;
        std::cout << "END = " << end.row << " " << end.col << std::endl;

        current.col *= 2;
        current.row *= 2;

        std::map<Point<int>, Point<int>> parent;

        //int r = 0;

        while(current != end){
            //r++;
            Action action = selectMaxAction(qTable, current);

            Point<int> next = getNextPoint(current, action);

            parent[next] = current;

            // std::cout << "Current: " << current.row << " " << current.col << std::endl;
            // std::cout << "Next: " << next.row << " " << next.col << std::endl;

            current = next;

            if(count++ > 5000000){ 
                std::cout << "BREAK" << std::endl;
                break;
            }
        }

        reconstructPath(parent, {start_.col * 2 , start_.row * 2}, end);

        std::cout << "buildQPath END" << std::endl;
    }
}