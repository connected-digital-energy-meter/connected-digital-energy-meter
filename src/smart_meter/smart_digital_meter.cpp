#include "smart_digital_meter.h"
#include <ArduinoJson.h>
#include "../logging/logger.h"
#include "../digital_meter/decoder.h"
#include <ESP8266WiFi.h>
#include "../stats/meter_stats_to_json_converter.h"
#include "../digital_meter/datagram_to_json_converter.h"
#include "../system/system_details_to_json_converter.h"
#include "../version.h"

namespace CDEM {

  SmartDigitalMeter::SmartDigitalMeter(int requestPin, Stream * serial)
    : meter(requestPin, serial) {
  }

  void SmartDigitalMeter::set_publisher(IPublisher * publisher) {
    this->publisher = publisher;
  }

  void SmartDigitalMeter::start(const Configuration * config, DeviceStatus * deviceStatus) {
    this->deviceConfig = config;
    this->period = config->read_period() * 1000;
    this->deviceStatus = deviceStatus;

    // Start time for period
    acquireData = true;
    startMillis = millis();
    lastStatsPublish = startMillis;
    publish_startup_message();
  }

  void SmartDigitalMeter::stop(void) {
    acquireData = false;
  }

  void SmartDigitalMeter::process(void) {
    // Current time for period
    currentMillis = millis();

    // Wait until next period  
    if(acquireData && (currentMillis - startMillis) >= period) {

      switch (currentState) {

        // Request data
        case State::IDLE:
          meter.enable();
          currentState = State::READING_DATAGRAM;
          break;

        // Read data
        case State::READING_DATAGRAM: {
          DigitalMeter::MeterStatus status = meter.read_datagram(datagramBuffer, sizeof(datagramBuffer));
          if (status == DigitalMeter::MeterStatus::DATAGRAM_READY) {
            currentState = State::DATAGRAM_READY;
          } else if (status == DigitalMeter::MeterStatus::CRC_ERROR || status == DigitalMeter::MeterStatus::TIMED_OUT) {
            meter.disable();
            currentState = State::IDLE;
            startMillis = currentMillis;
            deviceStatus->meter_error();

            if (status == DigitalMeter::MeterStatus::TIMED_OUT) stats.increment_timeouts();
            else stats.increment_crc_errors();
          } // else MeterStatus::IN_PROGRESS
          break;
        }

        // Decode the datagram
        case State::DATAGRAM_READY:
          meter.disable();
          datagram = Decoder::decode(datagramBuffer, sizeof(datagramBuffer));
          DoLog.info("Successfully decoded datagram ready for publish", "smart");
          DoLog.verbose(datagram.to_string(), "smart");
          deviceStatus->meter_ok();
          stats.increment_decoded();

          if (publish_datagram()) stats.increment_published();
          currentState = State::IDLE;     // Ready for next request
          startMillis = currentMillis;    // Reset timer
          break;
      }
    }

    if (currentState != State::READING_DATAGRAM) {
      stats.update_uptime();
      
      if ((currentMillis - lastStatsPublish) >= STATS_PUBLISH_TIME) {
        if (!announceSend) publish_startup_message();
        DoLog.verbose("Publishing stats of smart meter", "smart");
        publish_stats();
        lastStatsPublish = millis();
      }

      if (publisher) publisher->process();
    }
  }

  bool SmartDigitalMeter::publish_datagram(void) {
    bool scheduleOk = true;
    
    std::vector<String> keys = datagram.keys();
    for (String key : keys) {
      scheduleOk = scheduleOk && publish(
        key,
        String(datagram.get(key))
      );
    }

    scheduleOk = scheduleOk && publish(
      "payload",
      DatagramToJsonConverter::to_json_string(&datagram)
    );
    
    if (scheduleOk) DoLog.info("Datagram scheduled for publish", "smart");
    else DoLog.warning("Failed to schedule datagram for publish", "smart");
      
    return scheduleOk;
  }

  bool SmartDigitalMeter::publish_stats(void) {
    return publish(
      "stats",
      MeterStatsToJsonConverter::to_json_string(&stats)
    );
  }

  void SmartDigitalMeter::publish_startup_message(void) {
    announceSend = publish(
      "announce",
      SystemDetailsToJsonConverter::to_json_string(
        WiFi.localIP().toString(),
        WiFi.macAddress(),
        CDEM_LIB_VERSION,
        "v4.0"      // TODO: Replace with actual hw version
      )
    );

    if (!announceSend) DoLog.warning("Failed to send announce via MQTT. Will retry later.", "smart");
    else DoLog.verbose("Announce message successfully send.", "smart");
  }

  bool SmartDigitalMeter::publish(String subtopic, String payload) {
    if (!publisher) {
      DoLog.warning("No MQTT publisher is set", "smart");
      return false;
    }

    String topic = deviceConfig->mqtt_topic() + "/" + subtopic;
    return publisher->publish(topic, payload);
  }

};