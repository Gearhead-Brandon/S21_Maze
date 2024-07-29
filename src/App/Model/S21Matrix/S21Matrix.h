#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cmath>
#include <cstring>

#define IncorrectValuesRowsOrColumns                                           \
  "Incorrect values for initialization, rows and cols should be > 0 "
#define IncorrectValuesRowsOrColumnsResize                                     \
  "Incorrect values for resize, rows and cols should be > 0 "
#define DiffSizesMatrices "Different matrix dimensions"
#define DiffSizesMatrices "Different matrix dimensions"
#define NumColsNotEqNumRows                                                    \
  "The number of columns of the first matrix is not equal to the number of "   \
  "rows of the second matrix"
#define MatrixNotSquare "The matrix is not square."
#define DetIsZero "The determinant of the matrix is zero"
#define IndexesOutOfRange "Indexes is out of range"

namespace s21{
  
  template <typename T>
  class S21Matrix {

  private:

    int rows_, cols_; // rows and columns attributes
    T** matrix_;      // pointer to the memory where the matrix will be allocated

    void CreateMatrix();

  public:
    S21Matrix();
    S21Matrix(size_t rows, size_t cols);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other);
    S21Matrix& operator=(const S21Matrix &other);
    S21Matrix& operator=(S21Matrix &&other);
    ~S21Matrix();                 

    int GetRows() const;
    int GetCols() const;

    void SetRows(int newRows);
    void SetCols(int newCols);
    void Resize(int new_rows, int new_cols);

    bool Equal(const S21Matrix &other) const;

    void swap(S21Matrix &other);

    bool operator==(const S21Matrix &other) const;

    T& operator()(int row, int col) const;

    void FillNumbers(T num);
    bool PrintMatrix() const;
  };
}

#include "S21Matrix.tpp"

#endif
