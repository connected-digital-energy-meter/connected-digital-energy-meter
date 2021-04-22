#pragma once

#include "validator.h"

namespace CDEM {

  class IpValidator : public Validator {

    public:
      virtual bool is_valid(String value);
  };

};