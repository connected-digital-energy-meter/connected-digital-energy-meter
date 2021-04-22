#include "number_validator.h"
#include "../helpers/string_helper.h"

namespace CDEM {

  NumberValidator::NumberValidator(long minimum, long maximum) {
    this->minimum = minimum;
    this->maximum = maximum;
  }

  bool NumberValidator::is_valid(String value) {
    if (!StringHelper::is_number(value)) {
      this->validation_error("Value is not a valid number");
      return false;
    }

    long number = value.toInt();

    if (number < minimum) {
      this->validation_error("Value should not be smaller than " + String(minimum));
      return false;
    } else if (number > maximum) {
      this->validation_error("Value should not be larger than " + String(maximum));
      return false;
    }

    return true;
  }

};