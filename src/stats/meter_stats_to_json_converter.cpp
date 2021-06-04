#include "meter_stats_to_json_converter.h"
#include <ArduinoJson.h>

namespace CDEM {

  String MeterStatsToJsonConverter::to_json_string(const MeterStats * stats) {
    StaticJsonDocument<128> json;
    json["decoded"] = stats->decoded();
    json["timeouts"] = stats->timeouts();
    json["published"] = stats->published();
    json["crcerrors"] = stats->crc_errors();

    String result = "";
    serializeJson(json, result);

    return result;
  }

};