/**
 * @file Cave.h
 * @brief Header file describing the class Cave
 */

#ifndef CAVE_H
#define CAVE_H

#include <iostream>
#include <vector>

#include "../../Common/Structures/Observer/Observable/Observable.h"
#include "../../Common/Structures/OpResult/OpResult.h"
#include "../../Common/Structures/Primitives/Line.h"
#include "../../Common/Structures/Primitives/Point.h"
#include "../../Common/Structures/Primitives/Rect.h"
#include "../S21Matrix/S21Matrix.h"

namespace s21 {

/**
 * @brief Class describing the cave
 * @details Model implements the interface Observable
 */
class Cave : public Observable {
  //! Cave matrix
  S21Matrix<char> caveMatrix_;

 public:
  /**
   * @brief Default constructor
   */
  Cave();

  /**
   * @brief Default destructor
   */
  ~Cave() = default;

  /**
   * @brief The load method cave from file
   * @param path - path to the file
   * @return Operation result
   */
  OpResult load(const std::string &path);

  /**
   * @brief The generate method cave
   * @param rows - number of rows
   * @param cols - number of columns
   * @param initChance - chance of initial living cells
   * @return Operation result
   */
  OpResult generate(int rows, int cols, int initChance);

  /**
   * @brief The transform method cave
   * @param full - is full transform or not
   * @param birthLimit - birth limit
   * @param deathLimit - death limit
   * @param time - time in milliseconds
   * @return Operation result
   */
  OpResult transform(bool full, int birthLimit, int deathLimit, int time);

  /**
   * @brief The get method cave
   * @param width - width of the cave
   * @param height - height of the cave
   * @return Vector of cells
   */
  std::vector<Rect> get(float width, float height);

 private:
  /**
   * @brief Count living neighbors
   * @param field - field
   * @param row - row
   * @param col - column
   * @return Count of living neighbors
   */
  int countLivingNeighbors(S21Matrix<char> field, int row, int col);

  /**
   * @brief Parameters check
   * @param birthLimit - birth limit
   * @param deathLimit - death limit
   * @param time - time
   * @return Operation result
   */
  OpResult parametersCheck(int birthLimit, int deathLimit, int time);

  /**
   * @brief One step transform cave
   * @param birthLimit - birth limit
   * @param deathLimit - death limit
   */
  void oneStepTransform(int birthLimit, int deathLimit);
};
}  // namespace s21

#endif