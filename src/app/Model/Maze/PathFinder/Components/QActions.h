#ifndef QActions_H
#define QActions_H

#include <vector>

namespace s21{
    enum class Action : int {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };

    struct QActions{
        // left, up, right, down
        std::vector<float> qValues;

        QActions() : qValues(4, 0.0f){}

        // float left;
        // float up;
        // float right;
        // float down;

        // StateAction() : left(0.0f), up(0.0f), right(0.0f), down(0.0f){}
    };
}

#endif