#ifndef POINT_H
#define POINT_H

namespace s21{
    template <typename T>
    struct Point{
        T col; // column
        T row; // row

        bool operator==(const Point<T> &other) const {
            return col == other.col && row == other.row;
        }

        bool operator!=(const Point<T> &other) const {
            return col != other.col || row != other.row;
        }

        bool operator<(const Point<T> &other) const {
            return row < other.row || (row == other.row && col < other.col);
        }

        bool operator>(const Point<T> &other) const {
            return row > other.row || (row == other.row && col > other.col);
        }
    };
}

#endif