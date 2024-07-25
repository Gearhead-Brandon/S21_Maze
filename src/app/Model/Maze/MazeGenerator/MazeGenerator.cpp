#include "MazeGenerator.h"

namespace s21{

MazeGenerator::MazeGenerator(S21Matrix<char>& verticalMatrix, S21Matrix<char>& horizontalMatrix, int rows, int cols)
    : verticalMatrix_(verticalMatrix)
    , horizontalMatrix_(horizontalMatrix)
    , mazeLine_(cols, 0)
    , setCounter_(1)
    , rows_(rows)
    , cols_(cols){}

OpResult MazeGenerator::generateMaze(){
    verticalMatrix_.Resize(rows_, cols_);
    verticalMatrix_.FillNumbers('0');

    horizontalMatrix_.Resize(rows_, cols_);
    horizontalMatrix_.FillNumbers('0');

    for(int i = 0; i < rows_ - 1 ; i++){
        assignUniqueSets();
        setVerticalWalls(i);
        setHorizontalWalls(i);
       // horizontalWallsCheck(i);
        updateLine(i);
    }

    setEndLine();

    return {true, ""};
}

    void MazeGenerator::assignUniqueSets(){
        for(int i = 0; i < cols_; i++)
            if(!mazeLine_[i])
                mazeLine_[i] = setCounter_++;
    }

    char MazeGenerator::random(){
        return rand() % 2 ? '1' : '0';
    }

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

    void MazeGenerator::mergeSet(int index){
        int set = mazeLine_[index + 1];
        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set)
                mazeLine_[i] = mazeLine_[index];
    }

    void MazeGenerator::setHorizontalWalls(int row){
        for(int i = 0; i < cols_; i++){
            char choice = random();
            // int uniqueSet = countUniqueSet(mazeLine_[i]);
            // int horizontalWalls = countHorizontalWalls(mazeLine_[i], row);

            if(choice == '1' && countUniqueSet(mazeLine_[i]) != 1)
                horizontalMatrix_(row, i) = '1';

            if(!countHorizontalWalls(mazeLine_[i], row))
                horizontalMatrix_(row, i) = '0';
        }
    }

    int MazeGenerator::countUniqueSet(int set){
        int counter = 0;

        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set)
                counter++;

        return counter;
    }

    // void MazeGenerator::horizontalWallsCheck(int row){
    //     for(int i = 0; i < cols_; i++)
    //         if(!countHorizontalWalls(mazeLine_[i], row))
    //             horizontalMatrix_(row, i) = '0';
    // }

    int MazeGenerator::countHorizontalWalls(int set, int row){
        int counter = 0;

        for(int i = 0; i < cols_; i++)
            if(mazeLine_[i] == set && horizontalMatrix_(row, i) == '0')
                counter++;

        return counter;
    }

    void MazeGenerator::updateLine(int row){
        for(int i = 0; i < cols_; i++)
            if(horizontalMatrix_(row, i) == '1')
                mazeLine_[i] = 0;
    }

    void MazeGenerator::setEndLine(){
        assignUniqueSets();
        setVerticalWalls(rows_ - 1);
        endLineCheck();
    }

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