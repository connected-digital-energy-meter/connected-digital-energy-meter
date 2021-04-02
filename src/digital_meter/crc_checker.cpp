#include "crc_checker.h"

namespace CDEM {

  // Gets position number in char array
  int CrcChecker::find_char(const char* array, size_t size, char c) {
    const char* end = array + size;
    const char* match = std::find(array, end, c);
    return (end == match) ? -1 : (match - array);
  }

  unsigned int CrcChecker::calculate_crc(char * begin, char * end) {
    unsigned int crc = 0;
    char * currentChar = begin;

    while (currentChar <= end)
    {
      crc ^= (unsigned int)(*currentChar);
      int bit = 0;
      while (bit < 8) {
        if ((crc & 1) != 0) {
            crc = (crc >> 1) ^ 0xA001;
        }
        else crc >>= 1;
        bit++;
      }
      currentChar++;
    }

    return crc;
  }

  // Checks the CRC for the datagram
  bool CrcChecker::check_crc(char* buffer, size_t bufferlength) {
    // Find boundaries of the datagram
    int begin = find_char(buffer, bufferlength, '/');
    int end = find_char(buffer, bufferlength, '!');
    if (begin == -1 || end == -1) return false;
                
    // Find the datagram validation CRC
    char crc_validation[5];
    strncpy(crc_validation, buffer+end+1, 4);
    crc_validation[4] = '\0';
    String crcvalidation = String(crc_validation);
    
    unsigned int crc = calculate_crc(buffer + begin, buffer + end);

    String crccalc(crc,HEX);
    crccalc.toUpperCase();
    while (crccalc.length() < 4) {
      crccalc = "0" + crccalc;
    }

    return(crccalc == crcvalidation);
  }

};