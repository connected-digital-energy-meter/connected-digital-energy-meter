#include "crc_checker.h"
#include <Arduino.h>

namespace CDEM {

  uint16_t CrcChecker::calculate_crc(const char * buffer, size_t bufferLength) {
    unsigned int crc = 0;

    for (unsigned int i = 0; i < bufferLength; i++) {
      crc ^= (unsigned int)(buffer[i]);
      int bit = 0;
      while (bit < 8) {
        if ((crc & 1) != 0) {
          crc = (crc >> 1) ^ 0xA001;
        }
        else crc >>= 1;
        bit++;
      }
    }

    return crc;
  }

  bool CrcChecker::is_crc_valid(const char * buffer, size_t bufferLength, uint16_t crc) {
    return (calculate_crc(buffer, bufferLength) == crc);
  }

};