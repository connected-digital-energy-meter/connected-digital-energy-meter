#include "meter_stats_to_json_converter.h"
#include <ArduinoJson.h>

namespace CDEM {

  String MeterStatsToJsonConverter::to_json_string(MeterStats * stats) {
    StaticJsonDocument<156> json;
    json["decoded"] = stats->decoded();
    json["timeouts"] = stats->timeouts();
    json["published"] = stats->published();
    json["crcerrors"] = stats->crc_errors();
    json["uptime"] = stats->uptime().to_string();

    String result = "";
    serializeJson(json, result);

    return result;
  }

};