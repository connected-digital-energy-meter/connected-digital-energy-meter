#pragma once

#include <Arduino.h>
#include "../utilities/serializable_map.h"

namespace CDEM {

  class Configuration {

    public:
      Configuration(void);

    public:
      void wifi_ssid(String ssid);
      String wifi_ssid(void) const;

      void wifi_password(String password);
      String wifi_password(void) const;

      void mqtt_broker(String broker);
      String mqtt_broker(void) const;

      void mqtt_port(int port);
      int mqtt_port(void) const;

      void mqtt_username(String username);
      String mqtt_username(void) const;

      void mqtt_password(String password);
      String mqtt_password(void) const;
      
      void mqtt_topic(String topic);
      String mqtt_topic(void) const;
      
      void use_dhcp(bool useDhcp);
      bool use_dhcp(void) const;
      
      void static_ip(String ip);
      String static_ip(void) const;
      
      void subnet_mask(String mask);
      String subnet_mask(void) const;
      
      void default_gateway(String gateway);
      String default_gateway(void) const;
      
      void read_period(unsigned int period);
      unsigned int read_period(void) const;
      
    public:
      String to_string(void) const;

    public:
      size_t serialize(char * buffer, size_t bufferSize) const;
      size_t deserialize(const char * buffer, size_t bufferSize);

    public:
      bool operator==(const Configuration& rhs) const;
      bool operator!=(const Configuration& rhs) const;

    private:
      SerializableMap datamap;
  };

};