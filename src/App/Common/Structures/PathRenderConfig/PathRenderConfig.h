/**
 * @file PathRenderConfig.h
 * @brief Header file describing the class PathRenderConfig
 */

#ifndef PATH_RENDER_CONFIG_H
#define PATH_RENDER_CONFIG_H

#include "../Primitives/Line.h"
#include "../Primitives/Rect.h"
#include <vector>

namespace s21{

    /**
     * @brief Class describing the config for path rendering
     */
    struct PathRenderConfig {

        //! Vector of the started and finished points
        std::vector<Rect> points_;

        //! Vector of the lines of the path
        std::vector<Line> path_;
    };
}

#endif