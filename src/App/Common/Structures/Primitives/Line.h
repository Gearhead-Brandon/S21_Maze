#ifndef LINE_H
#define LINE_H

typedef struct{
    float x;
    float y;
} Point;

typedef struct{
    Point begin;
    Point end;
}Line;

#endif