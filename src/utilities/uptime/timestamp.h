#pragma once

#include <Arduino.h>

namespace CDEM {

  class Timestamp {

    public:
      void add_days(unsigned long days);
      void add_hours(unsigned long hours);
      void add_minutes(unsigned long minutes);
      void add_seconds(unsigned long seconds);
      void add_milliseconds(unsigned long milliseconds);

    public:
      String to_string(void);

    private:
      unsigned int _milliseconds = 0;
      unsigned int _seconds = 0;
      unsigned int _minutes = 0;
      unsigned int _hours = 0;
      unsigned long _days = 0;
  };

};