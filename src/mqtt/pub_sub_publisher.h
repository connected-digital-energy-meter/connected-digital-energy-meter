#pragma once

#include "i_publisher.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

namespace CDEM {

  class PubSubPublisher : public IPublisher {

    public:
      PubSubPublisher(WiFiClient &wifiClient);
      ~PubSubPublisher(void);

    public:
      virtual void connect(String broker, unsigned int port);
      virtual void disconnect(void);
      virtual bool is_connected(void);

    public:
      virtual bool publish(String topic, String message);

    public:
      virtual void process(void);

    private:
      void build_client(void);
      void destroy_client(void);
      void connect(void);
    
    private:
      String broker = "";
      int port = 1883;
      WiFiClient &wifiClient;
      PubSubClient * client = nullptr;
      String clientId;
      const unsigned int CLIENT_BUFFER_SIZE = 1024;
      static const unsigned long RETRY_CONNECT_INTERVAL = 6000;
      unsigned long lastConnectTry = 0;
  };

};