#pragma once

#include "../mqtt/i_publisher.h"
#include "../config/configuration.h"
#include "../digital_meter/datagram.h"
#include "../digital_meter/digital_meter.h"
#include "../status/device_status.h"
#include "../stats/meter_stats.h"

namespace CDEM {

  class SmartDigitalMeter {

    public:
      SmartDigitalMeter(int requestPin, Stream * serial);

    public:
      void set_publisher(IPublisher * publisher);

    public:
      void start(const Configuration * config, DeviceStatus * deviceStatus);
      void stop(void);
      void process(void);   // Call this in loop()

    private:
      bool publish_datagram(void);
      bool publish_stats(void);

    private:
      void communications_check(void);

    private:
      // Define a program state class
      enum class State {
        IDLE,
        READING_DATAGRAM,
        DATAGRAM_READY
      };

    private:
      char datagramBuffer[1024] = {0};
      Datagram datagram;
      DigitalMeter meter;
      IPublisher * publisher = nullptr;
      bool acquireData = false;

      const Configuration * deviceConfig;

      // Set for periodic measurement
      long period = 10000L;
      unsigned long startMillis;
      unsigned long currentMillis;

      // Declare State and set state to IDLE
      State currentState = State::IDLE;

      unsigned long lastCommCheck = 0;
      DeviceStatus * deviceStatus;
      MeterStats stats;
      unsigned long lastStatsPublish = 0;

      const static unsigned int MAX_DATAGRAM_JSON_SIZE = 1000;
      const static unsigned long STATS_PUBLISH_TIME = 60000L;
  };

};