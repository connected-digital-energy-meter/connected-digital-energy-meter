#include "datagram.h"

namespace CDEM {

  void Datagram::set(String key, double value) {
    data[key] = value;
  }

  double Datagram::get(String key) {
    std::map<String,double>::iterator it = data.find(key);
    if (it == data.end()) return 0.0;

    return data[key];
  }

  std::vector<String> Datagram::keys(void) {
    std::vector<String> dataKeys;
    for(std::map<String,double>::iterator it = data.begin(); it != data.end(); it++) {
      dataKeys.push_back(it->first);
    }
    return dataKeys;
  }

  String Datagram::to_string() {
    String output = "Datagram:\n";

    for(std::map<String,double>::iterator it = data.begin(); it != data.end(); it++) {
      output += "\t " + it->first + ": " + String(it->second) + (it != data.end() ? "\n" : "");
    }

    return output;
  }

};