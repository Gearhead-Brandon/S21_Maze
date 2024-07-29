#ifndef PATH_RENDER_CONFIG_H
#define PATH_RENDER_CONFIG_H

#include "../Primitives/Line.h"
#include "../Primitives/Rect.h"
#include <vector>

namespace s21{

    struct PathRenderConfig {
        std::vector<Rect> points_;
        std::vector<Line> path_;
    };
}

#endif