/**
 * @file Line.h
 * @brief Header file describing the class Line
 */

#ifndef LINE_H
#define LINE_H

#include "Point.h"

namespace s21 {

/**
 * @class Line
 */
struct Line {
  //! First point of the line
  Point<float> begin;

  //! Second point of the line
  Point<float> end;

  /**
   * @brief Equality comparison operator
   */
  bool operator==(const Line &other) const {
    return begin == other.begin && end == other.end;
  }
};
}  // namespace s21

#endif