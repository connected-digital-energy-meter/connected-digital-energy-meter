#pragma once

#include <Arduino.h>
#include "meter_stats.h"

namespace CDEM {

  class MeterStatsToJsonConverter {

    public:
      static String to_json_string(MeterStats * stats);

  };

};