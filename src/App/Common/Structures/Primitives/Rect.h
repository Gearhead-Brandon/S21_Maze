/**
 * @file Rect.h
 * @brief Header file describing the class Rect
 */

#ifndef RECT_H
#define RECT_H

namespace s21 {

/**
 * @brief The class Rect
 */
struct Rect {
  //! The x coordinate
  float x;

  //! The y coordinate
  float y;

  //! The width
  float width;

  //! The height
  float height;

  /**
   * @brief The default constructor
   */
  Rect() : x(0), y(0), width(0), height(0) {}

  /**
   * @brief The parametrized constructor
   */
  Rect(float x, float y, float width, float height)
      : x(x), y(y), width(width), height(height) {}

  /**
   * @brief The equality operator
   */
  bool operator==(const Rect &other) const {
    return x == other.x && y == other.y && width == other.width &&
           height == other.height;
  }
};
}  // namespace s21

#endif