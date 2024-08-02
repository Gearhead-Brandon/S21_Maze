/**
 * @file S21Matrix.tpp
 * @brief Implementation of the class S21Matrix
 */

#include "S21Matrix.h"

namespace s21{

    /**
     * @brief Default constructor
     */
    template <typename T>
    S21Matrix<T>::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

    /**
     * @brief Parameterized constructor
     * @param rows count of rows
     * @param cols count of columns
     */
    template <typename T>
    S21Matrix<T>::S21Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols){
        CreateMatrix();
    }

    /**
     * @brief Create matrix
     */
    template <typename T>
    void S21Matrix<T>::CreateMatrix() {

        if (rows_ > 0 && cols_ > 0) {

            matrix_ = new T *[rows_];

            for (int i = 0; i < rows_; i++)
                matrix_[i] = new T[cols_];
        }else if (rows_ == 0 && cols_ == 0){
            matrix_ = nullptr;
        } else
            throw std::invalid_argument(IncorrectValuesRowsOrColumns);
    }

    /**
     * @brief Copy constructor
     * @param other
     */
    template <typename T>
    S21Matrix<T>::S21Matrix(const S21Matrix &other) : matrix_(nullptr), rows_(other.rows_), cols_(other.cols_) {
        S21Matrix temp(other.rows_, other.cols_);

        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                temp.matrix_[i][j] = other.matrix_[i][j];

        swap(temp);
    }

    /**
     * @brief Move constructor
     * @param other
     */
    template <typename T>
    S21Matrix<T>::S21Matrix(S21Matrix &&other)
        : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }

    /**
     * @brief Destructor
     */
    template <typename T>
    S21Matrix<T>::~S21Matrix() {  
        if (matrix_) {
            for (int i = 0; i < rows_; i++)
                delete[] matrix_[i];

            delete[] matrix_; 
        }
    }

    /**
     * @brief Get count of columns
     * @return count of columns
     */
    template <typename T>
    int S21Matrix<T>::GetCols() const { return cols_; }

    /**
     * @brief Get count of rows
     * @return count of rows
     */
    template <typename T>
    int S21Matrix<T>::GetRows() const { return rows_; }

    /**
     * @brief Check if two matrices are equal
     * @param other
     * @return true if two matrices are equal
     */
    template <typename T>
    bool S21Matrix<T>::Equal(const S21Matrix &other) const{
        if ((rows_ != other.rows_) || (cols_ != other.cols_))
            return false;

        for(int i = 0; i < rows_; i++)
            for(int j = 0; j < cols_; j++)
                if(matrix_[i][j] != other.matrix_[i][j])
                    return false;

        return true;
    }

    /**
     * @brief Fill matrix with numbers
     * @param num
     */
    template <typename T>
    void S21Matrix<T>::FillNumbers(T value) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] = value;
            }
        }
    }

    /**
     * @brief Resize matrix
     * @param new_rows
     * @param new_cols
     */
    template <typename T>
    void S21Matrix<T>::Resize(int newRows, int newCols) {
        if ((newRows < 0) || (newCols < 0))
            throw std::invalid_argument(IncorrectValuesRowsOrColumnsResize);

        S21Matrix<T> temp(newRows, newCols);

        int minRows = (newRows < rows_) ? newRows : rows_;
        int minCols = (newCols < cols_) ? newCols : cols_;
        
        for (int i = 0; i < minRows; i++)
            std::memcpy(temp.matrix_[i], matrix_[i], minCols * sizeof(T));

        swap(temp);
    }

    /**
     * @brief Set count of columns
     * @param newCols
     */
    template <typename T>
    void S21Matrix<T>::SetCols(int newCols) {
        if (newCols != cols_)
            Resize(rows_, newCols);
    }

    /**
     * @brief Set count of rows
     * @param newRows
     */
    template <typename T>
    void S21Matrix<T>::SetRows(int newRows) {
        if (newRows != rows_)
            Resize(newRows, cols_);
    }

    /**
     * @brief Operator () for access to the matrix
     * @param row
     * @param col
     * @return T&
     */
    template <typename T>
    T& S21Matrix<T>::operator()(int i, int j)  const {
        if((i < 0) || (j < 0) || (i >= rows_) || (j >= cols_))
            throw std::invalid_argument(IndexesOutOfRange);

        return matrix_[i][j];
    }

    /**
     * @brief Swap matrix
     * @param other
     */
    template <typename T>
    void S21Matrix<T>::swap(S21Matrix &other){
        std::swap(matrix_, other.matrix_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }

    /**
     * @brief Equal operator
     * @param other
     * @return true if two matrices are equal
     */
    template <typename T>
    bool S21Matrix<T>::operator==(const S21Matrix &other) const{
        return Equal(other);
    }
    
    /**
     * @brief Copy assignment operator
     * @param other
     */
    template <typename T>
    S21Matrix<T>& S21Matrix<T>::operator=(const S21Matrix &other) {
        S21Matrix temp(other);

        swap(temp);

        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other
     */
    template <typename T>
    S21Matrix<T>& S21Matrix<T>::operator=(S21Matrix &&other){
        S21Matrix temp(std::move(other));
        swap(temp);
        return *this;
    }
}