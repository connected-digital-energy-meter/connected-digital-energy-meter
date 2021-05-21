// #include "string_validator.h"

// namespace CDEM {

//   StringValidator::StringValidator(bool allowEmpty, unsigned int maxLength) {
//     this->allowEmpty = allowEmpty;
//     this->maxLength = maxLength;
//   }

//   bool StringValidator::is_valid(String value) {
//     if (!allowEmpty && value == "") {
//       this->validation_error("Value should not be empty.");
//       return false;
//     }



//     if (number < minimum) {
//       this->validation_error("Value should not be smaller than " + String(minimum));
//       return false;
//     } else if (number > maximum) {
//       this->validation_error("Value should not be larger than " + String(maximum));
//       return false;
//     }

//     return true;
//   }

// };