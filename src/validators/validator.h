#pragma once

#include <Arduino.h>

namespace CDEM {

  class Validator {

    public:
      virtual bool is_valid(String value) = 0;

    public:
      void validation_error(String message);
      String validation_error(void);

    private:
      String validationError = "";
  };

};