/**
 * @file Observable.cpp
 * @brief Source file with implementing the class Observable
 */

#include "Observable.h"

namespace s21 {

/**
 * @brief Adds an observer
 * @param observer Observer
 */
void Observable::addObserver(IObserver *observer) {
  _observers.push_back(observer);
}

/**
 * @brief Notifies the observer if some data was changed by the call of the
 * method update
 */
void Observable::notifyUpdate() {
  for (int i = 0; i < _observers.size(); i++) _observers[i]->update();
}
}  // namespace s21