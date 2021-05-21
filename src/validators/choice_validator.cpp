#include "choice_validator.h"

namespace CDEM {

  ChoiceValidator::ChoiceValidator(std::vector<String> choices, bool caseSensitive) {
    this->choices = choices;
    this->caseSensitive = caseSensitive;

    if (!caseSensitive) {
      for (unsigned int i = 0; i < choices.size(); i++) {
        choices[i].toLowerCase();
      }
    }
  }

  bool ChoiceValidator::is_valid(String value, String label) {
    if (!caseSensitive) {
      value.toLowerCase();
    }

    for (auto choice : choices) {
      if (choice == value) return true;
    }

    String error = "Given input is not a valid option. Possible options are:\n[";
    for (unsigned int i = 0; i < choices.size(); i++) {
      error += choices[i];
      if (i < choices.size()-1) error += "|";
    }
    error += "]";
    this->validation_error(error);

    return false;
  }

};