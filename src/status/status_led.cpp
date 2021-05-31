#include "status_led.h"
#include <Arduino.h>

namespace CDEM {

  StatusLed::StatusLed(int pin, bool inverted) {
    _pin = pin;
    _inverted = inverted;
    pinMode(_pin, OUTPUT);
    led_off();
  }

  StatusLed::~StatusLed(void) {
    stop();
  }

  void StatusLed::start(unsigned int onTime, unsigned int offTime, unsigned int delayTime) {
    _onTime = onTime;
    _offTime = offTime;
    _ticker.once_ms(delayTime, std::bind(&StatusLed::scheduled_on, this));
  }

  void StatusLed::stop(void) {
    led_off();
    _ticker.detach();
  }

  void StatusLed::scheduled_on(void) {
    led_on();
    _ticker.once_ms(_onTime, std::bind(&StatusLed::scheduled_off, this));
  }

  void StatusLed::scheduled_off(void) {
    led_off();
    _ticker.once_ms(_offTime, std::bind(&StatusLed::scheduled_on, this));
  }

  void StatusLed::led_on(void) {
    digitalWrite(_pin, (_inverted ? LOW : HIGH));
  }

  void StatusLed::led_off(void) {
    digitalWrite(_pin, (_inverted ? HIGH : LOW));
  }

};