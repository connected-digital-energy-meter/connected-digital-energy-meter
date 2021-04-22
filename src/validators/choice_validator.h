#pragma once

#include "validator.h"
#include <Arduino.h>
#include <vector>

namespace CDEM {

  class ChoiceValidator : public Validator {

    public:
      ChoiceValidator(std::vector<String> choices, bool caseSensitive=false);

    public:
      virtual bool is_valid(String value);

    private:
      std::vector<String> choices;
      bool caseSensitive = false;
  };

};