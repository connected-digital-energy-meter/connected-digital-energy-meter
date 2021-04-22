#pragma once

# include <Arduino.h>
#include <vector>

namespace CDEM {

  class StringHelper {

    public:
      static bool is_number(String value);
      static size_t count_characters(String text, char symbol);
      static std::vector<String> split(String text, char delimiter, bool includeEmpty=true);

  };

};