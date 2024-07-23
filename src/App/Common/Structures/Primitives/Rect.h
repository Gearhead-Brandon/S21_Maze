#ifndef RECT_H
#define RECT_H

namespace s21{
    struct Rect{
        float x;
        float y;
        float width;
        float height;

        Rect() : x(0), y(0), width(0), height(0) {}
        
        Rect(float x, float y, float width, float height) 
            : x(x), y(y), width(width), height(height) {}
    };
}

#endif