/**
 * @file MazeGenerator.cpp
 * @brief Implementation of the class MazeGenerator
 */

#include "MazeGenerator.h"

namespace s21{

    /**
     * @brief Parametrized constructor
     * @param verticalMatrix - reference to the matrix of vertical walls
     * @param horizontalMatrix - reference to the matrix of horizontal walls
     * @param rows - number of rows
     * @param cols - number of columns
     */
    MazeGenerator::MazeGenerator(S21Matrix<char>& verticalMatrix, S21Matrix<char>& horizontalMatrix, int rows, int cols)
        : verticalMatrix_(verticalMatrix)
        , horizontalMatrix_(horizontalMatrix)
        , mazeLine_(cols, 0)
        , setCounter_(1)
        , rows_(rows)
        , cols_(cols){}

    /**
     * @brief Generate maze 
     * @return Operation result
     */
    OpResult MazeGenerator::generate(){
        verticalMatrix_.Resize(rows_, cols_);
        verticalMatrix_.FillNumbers('0');

        horizontalMatrix_.Resize(rows_, cols_);
        horizontalMatrix_.FillNumbers('0');

        for(int i = 0; i < rows_ - 1 ; i++){
            assignUniqueSets();
            setVerticalWalls(i);
            setHorizontalWalls(i);
            updateLine(i);
        }

        setEndLine();

        return {true, ""};
    }

    /**
     * @brief Assign unique sets to the current line of the maze
     */
    void MazeGenerator::assignUniqueSets(){
        for(int i = 0; i < cols_; i++)
            if(!mazeLine_[i])
                mazeLine_[i] = setCounter_++;
    }

    /**
     * @brief Random number generator
     * @return Random number
     */
    char MazeGenerator::random(){
        return rand() % 2 ? '1' : '0';
    }

    /**
     * @brief Set vertical walls for the current row
     * @param row - current row
     */
    void MazeGenerator::setVerticalWalls(int row){
        for(int i = 0; i < cols_ - 1; i++){
            char choice = random();
            if(choice == '1' || mazeLine_[i] == mazeLine_[i + 1]){
                verticalMatrix_(row, i) = '1';
            }else
                mergeSet(i);
        }

        verticalMatrix_(row, cols_ - 1) = '1';
    }

    /**
     * @brief Merge sets in the current line
     * @param index - index of the current cell
     */
    void MazeGenerator::mergeSet(int index){
        int set = mazeLine_[index + 1];
        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set)
                mazeLine_[i] = mazeLine_[index];
    }

    /**
     * @brief Set horizontal walls for the current row
     * @param row - current row
     */
    void MazeGenerator::setHorizontalWalls(int row){
        for(int i = 0; i < cols_; i++){
            char choice = random();

            if(choice == '1' && countUniqueSet(mazeLine_[i]) != 1)
                horizontalMatrix_(row, i) = '1';

            if(!countHorizontalWalls(mazeLine_[i], row))
                horizontalMatrix_(row, i) = '0';
        }
    }

    /**
     * @brief Count unique sets in the current line
     * @param num - number of the current line
     * @return Count of unique sets
     */
    int MazeGenerator::countUniqueSet(int set){
        int counter = 0;

        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set)
                counter++;

        return counter;
    }

    /**
     * @brief Count horizontal walls in the current line
     * @param num - number of the current line
     * @param row - current row
     * @return Count of horizontal walls
     */
    int MazeGenerator::countHorizontalWalls(int set, int row){
        int counter = 0;

        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set && horizontalMatrix_(row, i) == '0')
                counter++;

        return counter;
    }

    /**
     * @brief Update line of the maze
     * @param row - current row
     */
    void MazeGenerator::updateLine(int row){
        for(int i = 0; i < cols_; i++)
            if(horizontalMatrix_(row, i) == '1')
                mazeLine_[i] = 0;
    }

    /**
     * @brief Set end line
     */
    void MazeGenerator::setEndLine(){
        assignUniqueSets();
        setVerticalWalls(rows_ - 1);
        endLineCheck();
    }

    /**
     * @brief End line check
     */
    void MazeGenerator::endLineCheck(){
        for(int i = 0; i < cols_ - 1; i++){
            if(mazeLine_[i] != mazeLine_[i + 1]){
                verticalMatrix_(rows_ - 1, i) = '0';
                mergeSet(i);
            }

            horizontalMatrix_(rows_ - 1, i) = '1';
        }

        horizontalMatrix_(rows_ - 1, cols_ - 1) = '1';
    }
}