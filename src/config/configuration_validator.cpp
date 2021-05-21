#include "configuration_validator.h"
#include "../validators/string_validator.h"

namespace CDEM {

  String ConfigurationValidator::validate_ssid(String ssid) {
    StringValidator validator(false, 5);
    validator.is_valid(ssid, "SSID");
    return validator.validation_error();
  }

};