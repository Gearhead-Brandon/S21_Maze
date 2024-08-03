/**
 * @file PathFinder.h
 * @brief Header file describing the class PathFinder
 */

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <cmath>
#include <map>
#include <random>

#include "../../../Common/Structures/OpResult/OpResult.h"
#include "../../../Common/Structures/PathRenderConfig/PathRenderConfig.h"
#include "../../../Common/Structures/Primitives/Point.h"
#include "../../S21Matrix/S21Matrix.h"
#include "Components/QActions.h"

namespace s21 {

/**
 * @brief Class describing the path finder algorithm
 */
class PathFinder {
  //! Starting index of the path
  Point<int> start_;

  //! Ending index of the path
  Point<int> end_;

  //! Vector of indexes of the path
  std::vector<Point<int>> path_;

  //! Matrix of the maze
  S21Matrix<char> maze_;

  using QTable = std::vector<std::vector<QActions>>;

 public:
  /**
   * @brief Default constructor
   */
  PathFinder();

  /**
   * @brief Default destructor
   */
  ~PathFinder() = default;

  /**
   * @brief Set the start position of the path
   * @param start Start position
   * @param wRatio Width divide by count of columns
   * @param hRatio Height divide by count of rows
   */
  void setStartPosition(Point<float> start, float wRatio, float hRatio);

  /**
   * @brief Set the end position of the path
   * @param end End position
   * @param wRatio Width divide by count of columns
   * @param hRatio Height divide by count of rows
   */
  void setEndPosition(Point<float> end, float wRatio, float hRatio);

  /**
   * @brief Get the path
   * @param areaSize Size of the area
   * @return Configuration of the path
   */
  PathRenderConfig get(Point<float> areaSize);

  /**
   * @brief Set the maze
   * @param maze Matrix of the maze
   */
  void setMaze(S21Matrix<char>&& maze);

  /**
   * @brief Find the path through the Q-Learning algorithm
   * @param start Start position
   * @param goal Goal position
   * @return Operation result
   */
  OpResult QPathFinding(Point<int> start, Point<int> goal);

  /**
   * @brief Reset the path
   */
  void reset();

 private:
  /**
   * @brief Set the point to the path
   * @param el Point
   * @param config Configuration of the path
   * @param areaSize Size of the area
   */
  void setPointToPath(Point<int> el, PathRenderConfig& config,
                      Point<float> areaSize);

  /**
   * @brief Fill the path
   * @param config Configuration of the path
   * @param areaSize Size of the area
   */
  void fillPath(PathRenderConfig& config, Point<float> areaSize);

  /**
   * @brief Cost of the path from current to next
   * @param current Current point
   * @param next Next point
   * @return Cost
   */
  int calculateG(Point<int> current, Point<int> next);

  /**
   * @brief Heuristic function
   * @param point Point
   * @param goal Goal point
   * @return Heuristic
   */
  int calculateHeuristic(Point<int> point, Point<int> goal);

  /**
   * @brief Check if the point is not a wall
   * @param x X coordinate
   * @param y Y coordinate
   * @return True if the point is not a wall
   */
  bool isNotWall(int x, int y);

  /**
   * @brief Find the path through the A* algorithm
   */
  void findPathAStar();

  /**
   * @brief Reconstruct the path
   * @param parent Parent
   * @param start Start
   * @param end End
   */
  void reconstructPath(std::map<Point<int>, Point<int>>& parent,
                       const Point<int>& start, const Point<int>& end);

  /**
   * @brief Select the action
   * @param qTable QTable
   * @param currentPos Current position
   * @param epsilon Epsilon
   * @return Action
   */
  Action selectAction(const QTable& qTable, Point<int> currentPos,
                      float epsilon);

  /**
   * @brief Select the max action
   * @param qTable QTable
   * @param currentPos Current position
   * @return Action
   */
  Action selectMaxAction(const QTable& qTable, Point<int> currentPos);

  /**
   * @brief Get the next point
   * @param current Current point
   * @param action Action
   * @return Next point
   */
  Point<int> getNextPoint(Point<int> current, Action action);

  /**
   * @brief Get the reward
   * @param current Current point
   * @param next Next point
   * @param goal Goal point
   * @param done Done
   * @return Reward
   */
  float getReward(Point<int> current, Point<int>& next, Point<int> goal,
                  bool& done);

  /**
   * @brief Update the QTable
   * @param qTable QTable
   * @param currentState Current state
   * @param action Action
   * @param next Next state
   * @param reward Reward
   * @param alpha Alpha
   * @param gamma Gamma
   */
  void updateQTable(QTable& qTable, Point<int> currentState, Action action,
                    Point<int> next, float reward, float alpha, float gamma);

  /**
   * @brief Get the episodes count
   * @return Episodes count
   */
  int getEpisodesCount();

  /**
   * @brief Build the path
   * @param qTable QTable
   * @return Operation result
   */
  OpResult buildQPath(const QTable& qTable);

  /**
   * @brief Wrapper for the A* algorithm function
   * @param first First point
   * @param second Second point
   * @param copy Copy
   */
  void findPath(Point<int>& first, Point<int> second, Point<int> copy);
};
}  // namespace s21
#endif