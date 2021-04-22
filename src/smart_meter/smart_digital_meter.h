#pragma once

#include "../mqtt/i_publisher.h"
#include "../config/configuration.h"
#include "../digital_meter/datagram.h"
#include "../digital_meter/digital_meter.h"

namespace CDEM {

  class SmartDigitalMeter {

    public:
      SmartDigitalMeter(int requestPin, Stream * serial);

    public:
      void set_publisher(IPublisher * publisher);

    public:
      void start(Configuration * config);
      void stop(void);
      void process(void);   // Call this in loop()

    private:
      bool publish_datagram(void);

    private:
      // Define a program state class
      enum class State {
        IDLE,
        READING_DATAGRAM,
        DATAGRAM_READY,
        PROCESSING_DATAGRAM,
        DATAGRAM_DECODED
      };

    private:
      char datagramBuffer[1024] = {0};
      Datagram datagram;
      DigitalMeter meter;
      IPublisher * publisher = nullptr;
      bool acquireData = false;

      Configuration * deviceConfig;

      // Set for periodic measurement
      long period = 10000L;
      unsigned long startMillis;
      unsigned long currentMillis;

      // Declare State and set state to IDLE
      State currentState = State::IDLE;
  };

};