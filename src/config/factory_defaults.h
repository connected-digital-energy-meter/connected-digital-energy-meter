#pragma once

namespace CDEM {

  #define WIFI_DEFAULT_SSID         "IoTIsCool"
  #define WIFI_DEFAULT_PASSWORD     "IoT1337@HOME"

  #define MQTT_DEFAULT_BROKER       "192.168.0.1"
  #define MQTT_DEFAULT_PORT         1883
  #define MQTT_DEFAULT_TOPIC        "iot/myhome/cdem"

  #define NETWORK_USE_DHCP          true
  #define NETWORK_DEFAULT_IP        "192.168.12.1"
  #define NETWORK_DEFAULT_SUBNET    "255.255.0.0"
  #define NETWORK_DEFAULT_GATEWAY   "192.168.0.1"

  #define METER_DEFAULT_READ_PERIOD 60

};