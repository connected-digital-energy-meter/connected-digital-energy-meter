#include "meter_stats.h"

namespace CDEM {

  void MeterStats::increment_decoded(void) {
    _decoded++;
  }

  void MeterStats::increment_published(void) {
    _published++;
  }

  void MeterStats::increment_timeouts(void) {
    _timeouts++;
  }

  void MeterStats::increment_crc_errors(void) {
    _crcErrors++;
  }

  uint32_t MeterStats::decoded(void) const {
    return _decoded;
  }

  uint32_t MeterStats::published(void) const {
    return _published;
  }

  uint32_t MeterStats::timeouts(void) const {
    return _timeouts;
  }

  uint32_t MeterStats::crc_errors(void) const {
    return _crcErrors;
  }

  void MeterStats::update_uptime(void) {
    _uptime.update();
  }

  Uptime MeterStats::uptime(void) {
    return _uptime;
  }

  String MeterStats::to_string(void) {
    return "Decoded datagrams: " + String(decoded())
      + "\nPublished datagrams: " + String(published())
      + "\nTimeouts: " + String(timeouts())
      + "\nCRC Errors: " + String(crc_errors())
      + "\nUptime: " + _uptime.to_string();
  }

};