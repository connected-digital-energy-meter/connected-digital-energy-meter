#pragma once

#include <Arduino.h>
namespace CDEM {

  class ConfigurationValidator {

    public:
      static String validate_ssid(String ssid);

  };

};