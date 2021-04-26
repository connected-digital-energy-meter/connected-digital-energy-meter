#pragma once

#define METER_BAUDRATE            115200

#if defined(CDEM_PCB_V3)

  // TODO

#elif defined(CDEM_PCB_V4)

  // Serial for debugging
  #define SerialDebug               Serial
  #define SerialMeter               Serial

  // Digital meter config
  #define METER_REQUEST_PIN         13

#endif

