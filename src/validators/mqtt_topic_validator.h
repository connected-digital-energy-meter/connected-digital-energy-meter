#pragma once

#include "validator.h"

namespace CDEM {

  class MqttTopicValidator : public Validator {

    public:
      virtual bool is_valid(String value);
  };

};