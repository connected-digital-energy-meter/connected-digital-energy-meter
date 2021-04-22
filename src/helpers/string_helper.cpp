#include "string_helper.h"
#include <cctype>

namespace CDEM {

  bool StringHelper::is_number(String value) {
    if (value == "") return false;

    unsigned int start = 0;
    if (value[0] == '-' || value[0] == '+') start = 1;

    for (unsigned int i = start; i < value.length(); i++) {
      if (!std::isdigit(value[i])) return false;
    }

    return true;
  }

  size_t StringHelper::count_characters(String text, char symbol) {
    size_t count = 0;
    for (unsigned int i = 0; i < text.length(); i++) {
      if (text[i] == symbol) count++;
    }
    return count;
  }

  std::vector<String> StringHelper::split(String text, char delimiter, bool includeEmpty) {
    std::vector<String> parts;

    if (text.length() == 0) return parts;

    unsigned int start = 0;
    unsigned int next = 0;
    do {
      next = text.indexOf(delimiter, start);

      String part;
      if (next == start) {
        part = "";
      } else if (next != -1) {
        part = text.substring(start, next);    // Incl. from, Excl. to
      } else {
        part = text.substring(start, text.length());
      }

      if (includeEmpty || (!includeEmpty && part != "")) {
        parts.push_back(part);
      }

      start = next+1;

    } while (next != -1 && start < text.length());

    if (includeEmpty && text[text.length()-1] == delimiter) {
      parts.push_back("");
    }

    return parts;
  }

};