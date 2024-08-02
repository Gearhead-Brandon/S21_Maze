#ifndef CAVE_H
#define CAVE_H

#include <iostream>
#include <vector>
#include "../../Common/Structures/OpResult/OpResult.h"
#include "../../Common/Structures/Observer/Observable/Observable.h"
#include "../../Common/Structures/Primitives/Line.h"
#include "../../Common/Structures/Primitives/Rect.h"
#include "../../Common/Structures/Primitives/Point.h"
#include "../S21Matrix/S21Matrix.h"

namespace s21{
    class Cave : public Observable{

        S21Matrix<char> caveMatrix_;

    public:
        Cave();
        ~Cave() = default;

        OpResult load(const std::string &path);

        OpResult generate(int rows, int cols, int initChance);

        //OpResult transform(int birthLimit, int deathLimit);

        OpResult transform(bool full, int birthLimit, int deathLimit, int time);

        std::vector<Rect> get(float width, float height);

    private:
        int countLivingNeighbors(S21Matrix<char> field, int row, int col);
    
        OpResult parametersCheck(int birthLimit, int deathLimit);

        void oneStepTransform(int birthLimit, int deathLimit);
    };
}

#endif