#pragma once

#include <Arduino.h>

namespace CDEM {

  class CrcChecker {

    public:
      static bool check_crc(char* buffer, size_t bufferlength);

    private:
      static int find_char(const char* array, size_t size, char c);
      static unsigned int calculate_crc(char * begin, char * end);

  };

};