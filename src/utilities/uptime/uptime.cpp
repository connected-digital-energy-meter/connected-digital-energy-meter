#include "uptime.h"

namespace CDEM {

  void Uptime::update() {
    unsigned long now = millis();
    uptime.add_milliseconds(now-lastUpdate);
    lastUpdate = now;
  }

  String Uptime::to_string(void) {
    return uptime.to_string();
  }

};