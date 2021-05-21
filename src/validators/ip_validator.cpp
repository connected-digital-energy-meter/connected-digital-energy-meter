#include "ip_validator.h"
#include "number_validator.h"
#include "../helpers/string_helper.h"
#include <vector>

namespace CDEM {

  bool IpValidator::is_valid(String value, String label) {
    std::vector<String> parts = StringHelper::split(value, '.');

    if (parts.size() != 4) {
      this->validation_error(label + " does not contain 4 dots");
      return false;
    }

    NumberValidator numberValidator(0, 255);
    for (String octet : parts) {
      if (!numberValidator.is_valid(octet)) {
        this->validation_error(label + " contains invalid octet not within range of 0 to 255");
        return false;
      }
    }

    return true;
  }

};