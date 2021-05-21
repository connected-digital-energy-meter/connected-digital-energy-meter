#include "string_validator.h"

namespace CDEM {

  StringValidator::StringValidator(bool allowEmpty, unsigned int maxLength) {
    this->allowEmpty = allowEmpty;
    this->maxLength = maxLength;
  }

  bool StringValidator::is_valid(String value, String label) {
    if (!allowEmpty && value == "") {
      this->validation_error(label + " should not be empty.");
      return false;
    }

    if (value.length() > maxLength) {
      this->validation_error(label + " should not be longer than " + String(maxLength) + " characters.");
      return false;
    }

    return true;
  }

};