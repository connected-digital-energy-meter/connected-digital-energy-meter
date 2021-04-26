#pragma once

#include "i_publisher.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace CDEM {

  class PubSubPublisher : public IPublisher {

    public:
      PubSubPublisher(WiFiClient &wifiClient);

    public:
      virtual void connect(String broker, unsigned int port);
      virtual void disconnect(void);
      virtual bool is_connected(void);

    public:
      virtual bool publish(String topic, String message);

    public:
      virtual void process(void);

    private:
      void connect(void);
    
    private:
      PubSubClient client;
      String clientId;
      const unsigned int CLIENT_BUFFER_SIZE = 1024;
  };

};