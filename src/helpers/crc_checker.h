#pragma once

#include <Arduino.h>

namespace CDEM {

  class CrcChecker {

    public:
      static uint16_t calculate_crc(const char * buffer, size_t bufferLength);
      static bool is_crc_valid(const char * buffer, size_t bufferLength, uint16_t crc);

  };

};