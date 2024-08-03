/**
 * @file OpResult.h
 * @brief Header file describing the class OpResult
 */

#ifndef FACADE_OPERATION_RESULT_H
#define FACADE_OPERATION_RESULT_H

#include <string>

namespace s21 {

/**
 * @brief The class OpResult is used to check the success of the facade
 * operations
 */
class OpResult {
  //! Operation success flag
  bool isSuccess_;

  //! Operation result message
  std::string errorMessage_;

 public:
  /**
   * @brief The constructor of the class OpResult
   * @param isSuccess Operation success flag
   * @param errorMessage Operation result message
   */
  OpResult(bool isSuccess, std::string errorMessage);

  /**
   * @brief The destructor of the class OpResult
   */
  ~OpResult() = default;

  /**
   * @brief Getter of the success flag
   * @return Operation success flag
   */
  bool IsSuccess();

  /**
   * @brief Getter of the result message
   * @return Operation result message
   */
  std::string getErrorMessage() const;
};
}  // namespace s21

#endif