#ifndef StateAction_H
#define StateAction_H

namespace s21{
    struct StateAction{
        float left;
        float top;
        float right;
        float bottom;

        StateAction() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f){}
    };
}

#endif