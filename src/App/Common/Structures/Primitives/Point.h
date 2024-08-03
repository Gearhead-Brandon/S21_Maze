/**
 * @file Point.h
 * @brief Header file describing the class Point
 */

#ifndef POINT_H
#define POINT_H

namespace s21 {

/**
 * @brief Class describing the point
 * @tparam T type of coordinates
 * @details Class describes the coordinates of the point
 */
template <typename T>
struct Point {
  //! Column
  T col;

  //! Row
  T row;

  /**
   * @brief Equality comparison operator
   */
  bool operator==(const Point<T> &other) const {
    return col == other.col && row == other.row;
  }

  /**
   * @brief Inequality comparison operator
   */
  bool operator!=(const Point<T> &other) const {
    return col != other.col || row != other.row;
  }

  /**
   * @brief Less than comparison operator
   * @details Compares the rows and columns
   */
  bool operator<(const Point<T> &other) const {
    return row < other.row || (row == other.row && col < other.col);
  }

  /**
   * @brief Greater than comparison operator
   * @details Compares the rows and columns
   */
  bool operator>(const Point<T> &other) const {
    return row > other.row || (row == other.row && col > other.col);
  }
};
}  // namespace s21

#endif