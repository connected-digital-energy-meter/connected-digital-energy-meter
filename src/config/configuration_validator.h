#pragma once

#include <Arduino.h>
namespace CDEM {

  class ConfigurationValidator {

    public:
      static String validate_ssid(String ssid);
      static String validate_password(String password);
      static String validate_dhcp(String dhcp);
      static String validate_static_ip(String ip);
      static String validate_subnet_mask(String mask);
      static String validate_gateway_ip(String gw);
      static String validate_broker_ip(String ip);
      static String validate_broker_port(String port);
      static String validate_broker_username(String username);
      static String validate_broker_password(String password);
      static String validate_mqtt_topic(String topic);
      static String validate_read_period(String period);

  };

};