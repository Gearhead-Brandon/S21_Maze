#ifndef LINE_H
#define LINE_H

#include "Point.h"

namespace s21{
// typedef struct{
//     float x;
//     float y;
// } Point;

    struct Line {
        Point<float> begin;
        Point<float> end;

        bool operator==(const Line &other) const {
            return begin == other.begin && end == other.end;
        }
    };
}

#endif