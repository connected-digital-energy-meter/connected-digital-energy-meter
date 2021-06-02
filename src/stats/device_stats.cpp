#include "device_stats.h"

namespace CDEM {

  void DeviceStats::increment_decoded(void) {
    decodedDatagrams++;
  }

  void DeviceStats::increment_published(void) {
    publishedDatagrams++;
  }

  void DeviceStats::increment_meter_timeouts(void) {
    meterTimeouts++;
  }

  void DeviceStats::increment_meter_crc_errors(void) {
    meterCrcErrors++;
  }

  uint32_t DeviceStats::decoded_datagrams(void) {
    return decodedDatagrams;
  }

  uint32_t DeviceStats::published_datagrams(void) {
    return publishedDatagrams;
  }

  uint32_t DeviceStats::meter_timeouts(void) {
    return meterTimeouts;
  }

  uint32_t DeviceStats::meter_crc_errors(void) {
    return meterCrcErrors;
  }

  String DeviceStats::to_string(void) {
    return "Decoded datagrams: " + String(decoded_datagrams())
      + "\nPublished datagrams: " + String(published_datagrams())
      + "\nMeter Timeouts: " + String(meter_timeouts())
      + "\nMeter CRC Errors: " + String(meter_crc_errors());
  }

};