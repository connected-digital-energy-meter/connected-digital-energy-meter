#include "decoder.h"

namespace CDEM {

  String Decoder::find_data_string(char * buffer, const char * key, bool hasUnit, unsigned int datablockNumber) {
    // Look for the OBIS reference
    char* position = strstr(buffer, key);

    if (!position) return "";

    // Start position of value blocks in form of (...)(....)(....)
    char* start = position + strlen(key);

    unsigned int datablockCount = 0;
    do {
      start = strchr(start, '(') + 1;
      datablockCount++;

      if (!start) return "";

    } while (datablockCount < datablockNumber);

    if (*start == ')') return "";   // Empty data block

    // Look for the end position of the value for this OBIS reference
    char * end = NULL;
    if (hasUnit) {
      end = strchr(start, '*') - 1;
    } else { 
      end = strchr(start, ')') - 1;
    }
    if (!end) return "";

    char tempbuffer[64] = {0};
    strncpy(tempbuffer, start, end-start+1);

    return String(tempbuffer);
  }

  bool Decoder::parse_data_value(char * _buffer, const char * key, double * value, bool hasUnit, unsigned int datablockNumber) {
    String text = find_data_string(_buffer, key, hasUnit, datablockNumber);

    if (text == "") return false;
    
    *value = text.toDouble();
    return true;
  }

  Datagram Decoder::decode(char * buffer, size_t bufferlength) {
    Datagram output;

    struct UtilityKeyValue {
      const char * key;
      const char * id;
      double value;
      bool unitted;
      unsigned int datablockNumber;
    };

    UtilityKeyValue listing[] = {
      { "1-0:1.8.1", "consumption_high_tarif", 0.0, true, 1 },
      { "1-0:1.8.2", "consumption_low_tarif", 0.0, true, 1 },
      { "1-0:2.8.1", "production_high_tarif", 0.0, true, 1 },
      { "1-0:2.8.2", "production_low_tarif", 0.0, true, 1 },
      { "1-0:1.7.0", "total_power_consumption", 0.0, true, 1 },
      { "1-0:2.7.0", "total_power_production", 0.0, true, 1 },
      { "1-0:32.7.0", "actual_voltage_l1", 0.0, true, 1 },
      { "1-0:52.7.0", "actual_voltage_l2", 0.0, true, 1 },
      { "1-0:72.7.0", "actual_voltage_l3", 0.0, true, 1 },
      { "1-0:31.7.0", "actual_current_l1", 0.0, true, 1 },
      { "1-0:51.7.0", "actual_current_l2", 0.0, true, 1 },
      { "1-0:71.7.0", "actual_current_l3", 0.0, true, 1 },
      { "1-0:22.7.0", "l1_power_production", 0.0, true, 1 },
      { "1-0:42.7.0", "l2_power_production", 0.0, true, 1 },
      { "1-0:62.7.0", "l3_power_production", 0.0, true, 1 },
      { "1-0:21.7.0", "l1_power_consumption", 0.0, true, 1 },
      { "1-0:41.7.0", "l2_power_consumption", 0.0, true, 1 },
      { "1-0:61.7.0", "l3_power_consumption", 0.0, true, 1 },
      { "0-0:96.14.0", "actual_tarif", 0.0, false, 1 },
      { "0-1:24.2.3", "gas_meter_m3", 0.0, true, 2 },
      { "0-2:24.2.1", "water_meter_m3", 0.0, true, 2 },
      { "1-0:1.4.0", "current_average_demand", 0.0, true, 1},
      { "1-0:1.6.0", "maximum_demand_current_month", 0.0, true, 2}
      // { "0-0:98.1.0", "maximum_demand_last_year", 0.0, true, 2}  // TODO: is complexer, returns array of data
    };

    for (size_t i = 0; i < sizeof(listing)/sizeof(UtilityKeyValue); i++) {
      if (parse_data_value(buffer, listing[i].key, &(listing[i].value), listing[i].unitted, listing[i].datablockNumber)) {
        output.set(String(listing[i].id), listing[i].value);
      }
    }

    return output;
  }

};