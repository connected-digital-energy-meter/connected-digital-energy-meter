#pragma once

# include <Arduino.h>

namespace CDEM {

  class IPParser {

    public:
      // IP String should be valid !
      static IPAddress parse_ipv4(String ip);

  };

};