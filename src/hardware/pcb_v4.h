#pragma once

#if defined(CDEM_PCB_V3)

  // TODO

#elif defined(CDEM_PCB_V4)

  // Serial for debugging
  #define SerialDebug               Serial

  // Digital meter config
  #define METER_TX_PIN              14
  #define METER_BAUDRATE            115200
  #define METER_REQUEST_PIN         13

#endif

