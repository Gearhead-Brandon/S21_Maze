/**
 * @file QActions.h
 * @brief Header file describing the class QActions
 */

#ifndef QActions_H
#define QActions_H

#include <vector>

namespace s21{

    /**
     * @brief The enum Action describes the possible actions
     */
    enum class Action : int {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };

    /**
     * @brief The struct QActions describes the possible actions and their q-values
     */
    struct QActions{
        // left, up, right, down
        //! q-values
        std::vector<float> qValues;

        /**
         * @brief Default constructor
         */
        QActions() : qValues(4, 0.0f){}
    };
}

#endif