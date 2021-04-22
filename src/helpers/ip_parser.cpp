#include "ip_parser.h"
#include "string_helper.h"

namespace CDEM {

  IPAddress IPParser::parse_ipv4(String ip) {
    std::vector<String> parts = StringHelper::split(ip, '.', false);

    uint8_t octets[4];
    for (unsigned int i = 0; i < 4; i++) {
      octets[i] = (uint8_t)(parts[i].toInt());
    }

    return IPAddress(octets);
  }

};