#pragma once

#include <Arduino.h>
#include "datagram.h"

namespace CDEM {

  class DatagramToJsonConverter {

    public:
      static String to_json_string(Datagram * datagram);

    private:
      const static unsigned int MAX_DATAGRAM_JSON_SIZE = 1000;

  };

};