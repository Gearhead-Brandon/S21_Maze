/**
 * @file OpResult.cpp
 * @brief Source file with implementing the class OpResult
 */

#include "OpResult.h"

namespace s21 {

/**
 * @brief The constructor of the class OpResult
 * @param isSuccess Operation success flag
 * @param errorMessage Operation result message
 */
OpResult::OpResult(bool isSuccess, std::string errorMessage)
    : isSuccess_(isSuccess), errorMessage_(std::move(errorMessage)) {}

/**
 * @brief Getter of the success flag
 * @return Operation success flag
 */
bool OpResult::IsSuccess() { return isSuccess_; }

/**
 * @brief Getter of the result message
 * @return Operation result message
 */
std::string OpResult::getErrorMessage() const { return errorMessage_; }
}  // namespace s21