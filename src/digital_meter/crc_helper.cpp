#include "crc_helper.h"
#include "../helpers/crc_checker.h"

namespace CDEM {

  // Gets position number in char array
  int CrcHelper::find_char(const char* array, size_t size, char c) {
    const char* end = array + size;
    const char* match = std::find(array, end, c);
    return (end == match) ? -1 : (match - array);
  }

  uint16_t CrcHelper::calculate_crc(const char * begin, const char * end) {
    size_t length = end - begin + 1;
    return CrcChecker::calculate_crc(begin, length);
  }

  // Checks the CRC for the datagram
  bool CrcHelper::check_crc(const char* buffer, size_t bufferlength) {
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