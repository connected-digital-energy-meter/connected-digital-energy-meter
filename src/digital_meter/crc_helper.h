#pragma once

#include <Arduino.h>

namespace CDEM {

  class CrcHelper {

    public:
      static bool check_crc(const char* buffer, size_t bufferlength);

    private:
      static int find_char(const char* array, size_t size, char c);
      static uint16_t calculate_crc(const char * begin, const char * end);

  };

};