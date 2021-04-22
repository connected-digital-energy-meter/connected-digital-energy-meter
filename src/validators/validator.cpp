#include "validator.h"

namespace CDEM {

  void Validator::validation_error(String message) {
    validationError = message;
  }

  String Validator::validation_error(void) {
    return validationError;
  }

};