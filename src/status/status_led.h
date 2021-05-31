#pragma once

#include <Ticker.h>

namespace CDEM {

  class StatusLed {

    public:
      StatusLed(int pin, bool inverted=false);
    
    public:
      ~StatusLed(void);

    public:
      void start(unsigned int onTime, unsigned int offTime, unsigned int delayTime=0);
      void stop(void);

    private:
      void scheduled_on(void);
      void scheduled_off(void);

    public:
      void on(void);
      void off(void);

    private:
      int _pin;
      bool _inverted = false;
      unsigned int _onTime = 500;
      unsigned int _offTime = 500;

      Ticker _ticker;
  };

};