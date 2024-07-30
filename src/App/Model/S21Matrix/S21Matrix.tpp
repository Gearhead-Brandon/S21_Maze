#include "S21Matrix.h"

namespace s21{
    template <typename T>
    S21Matrix<T>::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

    template <typename T>
    S21Matrix<T>::S21Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols){
        CreateMatrix();
    }

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

    template <typename T>
    S21Matrix<T>::S21Matrix(const S21Matrix &other) : matrix_(nullptr), rows_(other.rows_), cols_(other.cols_) {
        S21Matrix temp(other.rows_, other.cols_);

        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                temp.matrix_[i][j] = other.matrix_[i][j];

        swap(temp);
    }

    template <typename T>
    S21Matrix<T>::S21Matrix(S21Matrix &&other)
        : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }

    template <typename T>
    S21Matrix<T>::~S21Matrix() {  
        if (matrix_) {
            for (int i = 0; i < rows_; i++)
                delete[] matrix_[i];

            delete[] matrix_; 
        }
    }

    template <typename T>
    int S21Matrix<T>::GetCols() const { return cols_; }

    template <typename T>
    int S21Matrix<T>::GetRows() const { return rows_; }

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

    template <typename T>
    void S21Matrix<T>::FillNumbers(T value) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] = value;
            }
        }
    }

    template <typename T>
    bool S21Matrix<T>::PrintMatrix() const {
        if (matrix_ == nullptr) {
            std::cout << "Matrix pointer is null in print" << std::endl;
            return false;
        }

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++)
                std::cout << matrix_[i][j];

            std::cout << std::endl;
        }

        return true;
    }

    template <typename T>
    void S21Matrix<T>::Resize(int newRows, int newCols) {
        if ((newRows < 0) || (newCols < 0))
            throw std::invalid_argument(IncorrectValuesRowsOrColumnsResize);

        S21Matrix<T> temp(newRows, newCols);

        int minRows = (newRows < rows_) ? newRows : rows_;
        int minCols = (newCols < cols_) ? newCols : cols_;

        // for (int i = 0; i < minRows; i++)
        //     for (int j = 0; j < minCols; j++)
        //         temp.matrix_[i][j] = matrix_[i][j];
        
        for (int i = 0; i < minRows; i++)
            std::memcpy(temp.matrix_[i], matrix_[i], minCols * sizeof(T));

        swap(temp);
    }

    template <typename T>
    void S21Matrix<T>::SetCols(int newCols) {
        if (newCols != cols_)
            Resize(rows_, newCols);
    }

    template <typename T>
    void S21Matrix<T>::SetRows(int newRows) {
        if (newRows != rows_)
            Resize(newRows, cols_);
    }

    template <typename T>
    T& S21Matrix<T>::operator()(int i, int j)  const {
        if((i < 0) || (j < 0) || (i >= rows_) || (j >= cols_))
            throw std::invalid_argument(IndexesOutOfRange);

        return matrix_[i][j];
    }

    template <typename T>
    void S21Matrix<T>::swap(S21Matrix &other){
        std::swap(matrix_, other.matrix_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }

    template <typename T>
    bool S21Matrix<T>::operator==(const S21Matrix &other) const{
        return Equal(other);
    }
    
    template <typename T>
    S21Matrix<T>& S21Matrix<T>::operator=(const S21Matrix &other) {
        S21Matrix temp(other);

        swap(temp);

        return *this;
    }

    template <typename T>
    S21Matrix<T>& S21Matrix<T>::operator=(S21Matrix &&other){
        S21Matrix temp(std::move(other));
        swap(temp);
        return *this;
    }
}