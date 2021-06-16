#pragma once

#include <Arduino.h>

namespace CDEM {

  class SystemDetailsToJsonConverter {

    public:
      static String to_json_string(String ip, String mac, String libVersion, String pcbVersion);

  };

};