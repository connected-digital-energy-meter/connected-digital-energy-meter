#pragma once

#include <Arduino.h>
#include "timestamp.h"

namespace CDEM {

  class Uptime {

    public:
      void update();

    public:
      String to_string(void);

    private:
      Timestamp uptime;
      unsigned long lastUpdate = 0;
  };

};