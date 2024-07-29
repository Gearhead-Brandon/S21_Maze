/**
 * @file Observable.h
 * @brief Header file describing the class Observable
 */

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "../IObserver.h"
#include <vector>

namespace s21 {

/**
 * @brief The class Observable
 * @details The class implements the Observer pattern
 *
 * Determines classes that will be observed by the observer. Notifies the
 * observer if some data was changed.
 */
class Observable {

  //! Storage of observers
  std::vector<IObserver *> _observers;

public:
  /**
   * @brief Adds an observer
   * @param observer Observer
   */
  void addObserver(IObserver *observer);

  /**
   * @brief Notifies the observer if some data was changed by the call of the
   * method update
   */
  void notifyUpdate();
};
} // namespace s21

#endif