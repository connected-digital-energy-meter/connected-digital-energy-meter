#include "system_details_to_json_converter.h"
#include <ArduinoJson.h>

namespace CDEM {

  String SystemDetailsToJsonConverter::to_json_string(String ip, String mac, String libVersion, String pcbVersion) {
    StaticJsonDocument<128> json;
    json["ip"] = ip;
    json["mac"] = mac;
    json["lib-version"] = libVersion;
    json["pcb-version"] = pcbVersion;

    String result = "";
    serializeJson(json, result);

    return result;
  }

};