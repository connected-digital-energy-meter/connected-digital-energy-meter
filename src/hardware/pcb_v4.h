#pragma once

#define METER_BAUDRATE            115200
#define SERIAL_DEBUG_BAUDRATE     115200

#if defined(CDEM_PCB_V3)
  #pragma message ( "Compiling for CDEM PCB v3" )

  // TODO

#elif defined(CDEM_PCB_V4)
  #pragma message ( "Compiling for CDEM PCB v4" )

  // Serial for debugging
  #define SerialDebug               Serial
  #define SerialMeter               Serial

  // Digital meter config
  #define METER_REQUEST_PIN         13

  // LEDs
  #define DATA_LED_PIN              12
  #define COMM_LED_PIN              5

  // WiFi
  #define PORTAL_WIFI_OUTPUT_POWER          16
  #define OPERATIONAL_WIFI_OUTPUT_POWER     18
    // Default = 20.5

  // Configuration
  #define EEPROM_CONFIG_ID                  0x0001
  #define EEPROM_CONFIG_SIZE                1024

#endif

