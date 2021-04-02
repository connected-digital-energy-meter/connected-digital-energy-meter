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
        IN_PROGRESS, DATAGRAM_READY, CRC_ERROR, TIMED_OUT
      };

    public:
      // Non-blocking function that tries to read some pieces of the datagram via a serial port.
      MeterStatus read_datagram(char * buffer, size_t bufferLength);

    private:
      void reset_read_state(void);
      void clear_buffer(char * buffer, size_t length);

    private:
      HardwareSerial * serial;
      int requestPin;
      unsigned int readPointer = 0;
      bool startDetected = false;
      unsigned long startTimeoutMillis = 0;
      static const unsigned long TIMEOUT_MS = 1000;
  };

};