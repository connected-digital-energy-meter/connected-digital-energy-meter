#pragma once

#include <Arduino.h>

namespace CDEM {

  class MeterStats {

    public:
      void increment_decoded(void);
      void increment_published(void);
      void increment_timeouts(void);
      void increment_crc_errors(void);
      
    public:
      uint32_t decoded(void) const;
      uint32_t published(void) const;
      uint32_t timeouts(void) const;
      uint32_t crc_errors(void) const;

    public:
      String to_string(void) const;

    private:
      uint32_t _decoded = 0;
      uint32_t _published = 0;
      uint32_t _timeouts = 0;
      uint32_t _crcErrors = 0;
  };

};