#pragma once

#include "validator.h"

namespace CDEM {

  class StringValidator : public Validator {

    public:
      StringValidator(bool allowEmpty, unsigned int maxLength);

    public:
      virtual bool is_valid(String value, String label="Value");

    private:
      bool allowEmpty;
      unsigned int maxLength;
  };

};