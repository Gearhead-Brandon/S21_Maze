#ifndef LINE_H
#define LINE_H

#include "Point.h"

namespace s21{
// typedef struct{
//     float x;
//     float y;
// } Point;

    typedef struct{
        Point<float> begin;
        Point<float> end;
    }Line;
}

#endif