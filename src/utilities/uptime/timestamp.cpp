#include "timestamp.h"

namespace CDEM {

  void Timestamp::add_days(unsigned long days) {
    _days += days;
  }

  void Timestamp::add_hours(unsigned long hours) {
    hours += _hours;
    unsigned long days = hours / 24;
    
    _hours = hours % 24;
    add_days(days);
  }

  void Timestamp::add_minutes(unsigned long minutes) {
    minutes += _minutes;
    unsigned long hours = minutes / 60;

    _minutes = minutes % 60;
    add_hours(hours);
  }

  void Timestamp::add_seconds(unsigned long seconds) {
    seconds += _seconds;
    unsigned long minutes = seconds / 60;

    _seconds = seconds % 60;
    add_minutes(minutes);
  }

  void Timestamp::add_milliseconds(unsigned long milliseconds) {
    milliseconds += _milliseconds;
    unsigned long seconds = milliseconds / 1000;

    _milliseconds = milliseconds % 1000;
    add_seconds(seconds);
  }

  String Timestamp::to_string(void) {
    return
      String(_days) + "d "
      + String(_hours) + "h "
      + String(_minutes) + "m "
      + String(_seconds) + "s "
      + String(_milliseconds) + "ms";
  }

};