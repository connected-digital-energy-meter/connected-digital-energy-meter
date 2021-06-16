#pragma once

#include "../config/configuration_manager.h"
#include "../status/device_status.h"

namespace CDEM {

  class System {

    public:
      static bool configure(ConfigurationManager * configManager, DeviceStatus * deviceStatus);
  };

};