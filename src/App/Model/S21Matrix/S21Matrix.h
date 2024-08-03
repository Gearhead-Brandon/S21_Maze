/**
 * @file S21Matrix.h
 * @brief Header file describing the class S21Matrix
 */

#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>

#define IncorrectValuesRowsOrColumns \
  "Incorrect values for initialization, rows and cols should be > 0 "
#define IncorrectValuesRowsOrColumnsResize \
  "Incorrect values for resize, rows and cols should be > 0 "
#define DiffSizesMatrices "Different matrix dimensions"
#define DiffSizesMatrices "Different matrix dimensions"
#define NumColsNotEqNumRows                                                  \
  "The number of columns of the first matrix is not equal to the number of " \
  "rows of the second matrix"
#define MatrixNotSquare "The matrix is not square."
#define DetIsZero "The determinant of the matrix is zero"
#define IndexesOutOfRange "Indexes is out of range"

namespace s21 {

/**
 * @brief Class describing the matrix
 * @tparam T type of matrix
 */
template <typename T>
class S21Matrix {
  //! Count of rows
  int rows_;

  //! Count of columns
  int cols_;

  //! Pointer to the matrix
  T **matrix_;

  /**
   * @brief Create matrix
   */
  void CreateMatrix();

 public:
  /**
   * @brief Default constructor
   */
  S21Matrix();

  /**
   * @brief Parameterized constructor
   * @param rows count of rows
   * @param cols count of columns
   */
  S21Matrix(size_t rows, size_t cols);

  /**
   * @brief Copy constructor
   * @param other
   */
  S21Matrix(const S21Matrix &other);

  /**
   * @brief Move constructor
   * @param other
   */
  S21Matrix(S21Matrix &&other);

  /**
   * @brief Copy assignment operator
   * @param other
   */
  S21Matrix &operator=(const S21Matrix &other);

  /**
   * @brief Move assignment operator
   * @param other
   */
  S21Matrix &operator=(S21Matrix &&other);

  /**
   * @brief Destructor
   */
  ~S21Matrix();

  /**
   * @brief Get count of rows
   * @return count of rows
   */
  int GetRows() const;

  /**
   * @brief Get count of columns
   * @return count of columns
   */
  int GetCols() const;

  /**
   * @brief Set count of rows
   * @param newRows
   */
  void SetRows(int newRows);

  /**
   * @brief Set count of columns
   * @param newCols
   */
  void SetCols(int newCols);

  /**
   * @brief Resize matrix
   * @param new_rows
   * @param new_cols
   */
  void Resize(int new_rows, int new_cols);

  /**
   * @brief Check if two matrices are equal
   * @param other
   * @return true if two matrices are equal
   */
  bool Equal(const S21Matrix &other) const;

  /**
   * @brief Swap matrix
   * @param other
   */
  void swap(S21Matrix &other);

  /**
   * @brief Equal operator
   * @param other
   * @return true if two matrices are equal
   */
  bool operator==(const S21Matrix &other) const;

  /**
   * @brief Operator () for access to the matrix
   * @param row
   * @param col
   * @return T&
   */
  T &operator()(int row, int col) const;

  /**
   * @brief Fill matrix with numbers
   * @param num
   */
  void FillNumbers(T num);
};
}  // namespace s21

#include "S21Matrix.tpp"

#endif
