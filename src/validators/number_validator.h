#pragma once

#include "validator.h"

namespace CDEM {

  class NumberValidator : public Validator {

    public:
      NumberValidator(long minimum, long maximum);

    public:
      virtual bool is_valid(String value, String label="Value");

    private:
      long minimum;
      long maximum; 
  };

};