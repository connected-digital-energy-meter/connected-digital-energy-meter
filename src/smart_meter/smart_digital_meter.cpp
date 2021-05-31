#include "smart_digital_meter.h"
#include <ArduinoJson.h>
#include "../logging/logger.h"
#include "../digital_meter/decoder.h"
#include <ESP8266WiFi.h>


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
    lastCommCheck = startMillis;
    communications_check();
  }

  void SmartDigitalMeter::stop(void) {
    acquireData = false;
  }

  void SmartDigitalMeter::process(void) {
    // Current time for period
    currentMillis = millis();

    if ((currentMillis - lastCommCheck) >= 10000) {
      communications_check();
      lastCommCheck = millis();
    }

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
          } // else MeterStatus::IN_PROGRESS
          break;
        }

        // Stop requesting data
        case State::DATAGRAM_READY:
          meter.disable();
          currentState = State::PROCESSING_DATAGRAM;
          break;

        // Decode data  
        case State::PROCESSING_DATAGRAM:
          datagram = Decoder::decode(datagramBuffer, sizeof(datagramBuffer));
          DoLog.info("Successfully decoded datagram ready for publish", "smart");
          DoLog.verbose(datagram.to_string(), "smart");
          currentState = State::DATAGRAM_DECODED;
          deviceStatus->meter_ok();
          break;

        // Publish data to MQTT
        case State::DATAGRAM_DECODED:
          publish_datagram();
          currentState = State::IDLE;     // Ready for next request
          startMillis = currentMillis;    // Reset timer
          break;
      }
    }

    if (publisher) publisher->process();
  }

  bool SmartDigitalMeter::publish_datagram(void) {
    if (publisher) {
      if (!publisher->is_connected()) {
        DoLog.warning("Could not publish. Publisher is not connected", "smart");
        return false;
      }

      bool schededuleOk = true;
      std::vector<String> keys = datagram.keys();

      StaticJsonDocument<1000> json;
      for (String key : keys) {
        String topic = deviceConfig->mqtt_topic() + "/" + key;
        String data = String(datagram.get(key));
        schededuleOk = schededuleOk && publisher->publish(topic, data);
        json[key] = datagram.get(key);
      }

      String payload = "";
      serializeJson(json, payload);
      String topic = deviceConfig->mqtt_topic() + "/payload";
      schededuleOk = schededuleOk && publisher->publish(topic, payload);
      
      if (schededuleOk) {
        DoLog.info("Datagram scheduled for publish", "smart");
      } else {
        DoLog.warning("Failed to schedule datagram for publish", "smart");
      }
      return schededuleOk;
    } else {
      DoLog.warning("No MQTT publisher is set", "smart");
    }

    return false;
  }

  void SmartDigitalMeter::communications_check(void) {
    if (WiFi.status() != WL_CONNECTED) {
      DoLog.warning("Not connected to WiFi", "comm-state");
      deviceStatus->connecting_wifi();
      return;
    }

    if (!publisher->is_connected()) {
      DoLog.warning("Not connected to MQTT broker", "comm-state");
      deviceStatus->wifi_no_mqtt();
      return;
    }
        
    DoLog.verbose("All operational", "comm-state");
    deviceStatus->communications_ok();
  }

};