#include "device_status.h"
#include <Arduino.h>

namespace CDEM {

  DeviceStatus::DeviceStatus(int dataLedPin, int commLedPin)
    : dataLed(dataLedPin, true), commLed(commLedPin, true) {
  }

  void DeviceStatus::clear(void) {
    dataLed.stop();
    commLed.stop();
  }

  void DeviceStatus::config_portal_up(void) {
    commLed.start(2000, 2000);
  }

  void DeviceStatus::not_configured(void) {
    clear();
    commLed.start(500, 500);
    dataLed.start(500, 500, 500);
  }

  void DeviceStatus::connecting_wifi(void) {
    commLed.stop();
  }

  void DeviceStatus::wifi_no_mqtt(void) {
    commLed.start(100, 900);    // Short flash
  }

  void DeviceStatus::communications_ok(void) {
    commLed.stop();
    commLed.on();
  }

  void DeviceStatus::meter_ok(void) {
    dataLed.stop();
    dataLed.on();
  }

  void DeviceStatus::meter_error(void) {
    dataLed.start(500, 500);
  }


};