#pragma once

#include <Arduino.h>

namespace CDEM {

  class DigitalMeter {

    public:
      DigitalMeter(int requestPin, HardwareSerial * serial);

    public:
      void enable(void);
      void disable(void);

    public:
      enum class MeterStatus {
        IN_PROGRESS, DATAGRAM_READY, CRC_ERROR
      };

    public:
      // Non-blocking function that tries to read some pieces of the datagram via a serial port.
      MeterStatus read_datagram(char * buffer, size_t bufferLength);

    private:
      void clear_buffer(char * buffer, size_t length);

    private:
      HardwareSerial * serial;
      int requestPin;
      unsigned int readPointer = 0;
      bool startDetected = false;
  };

};