#pragma once

#include "status_led.h"

namespace CDEM {

  class DeviceStatus {

    public:
      DeviceStatus(int dataLedPin, int commLedPin);

    public:   // Both LED's
      void clear(void);
      void not_configured(void);

    public:   // Communication
      void config_portal_up(void);
      void connecting_wifi(void);
      void wifi_no_mqtt(void);
      void communications_ok(void);

    // public:   // Data
    //   void meter_starting(void);
    //   void meter_data_ready(void);
    //   void meter_error(void);

    private:
      StatusLed dataLed;
      StatusLed commLed;
  };

};