#include "datagram_to_json_converter.h"
#include <ArduinoJson.h>

namespace CDEM {

  String DatagramToJsonConverter::to_json_string(Datagram * datagram) {
    std::vector<String> keys = datagram->keys();

    StaticJsonDocument<MAX_DATAGRAM_JSON_SIZE> json;
    for (String key : keys) {
        json[key] = datagram->get(key);
    }

    String result = "";
    serializeJson(json, result);
        
    return result;
  }

};
