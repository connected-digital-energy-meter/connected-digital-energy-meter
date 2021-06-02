#pragma once

#include <Arduino.h>

namespace CDEM {

  class DeviceStats {

    public:
      void increment_decoded(void);
      void increment_published(void);
      void increment_meter_timeouts(void);
      void increment_meter_crc_errors(void);
      
    public:
      uint32_t decoded_datagrams(void);
      uint32_t published_datagrams(void);
      uint32_t meter_timeouts(void);
      uint32_t meter_crc_errors(void);

    public:
      String to_string(void);

    private:
      uint32_t decodedDatagrams = 0;
      uint32_t publishedDatagrams = 0;
      uint32_t meterTimeouts = 0;
      uint32_t meterCrcErrors = 0;
  };

};