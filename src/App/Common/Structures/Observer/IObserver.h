/**
 * @file IObserver.h
 * @brief Header file describing the class IObserver
 */

#ifndef OBSERVER_H
#define OBSERVER_H

namespace s21 {

/**
 * @brief The class IObserver is used to notify about changes in the model
 */
class IObserver {
 public:
  /**
   * @brief Pure virtual function to notify about changes in the model
   */
  virtual void update() = 0;
};
}  // namespace s21

#endif  // OBSERVER_H