#pragma once

#include <Arduino.h>

namespace CDEM {

  class IPublisher {

    public:
      virtual void connect(String broker, unsigned int port, String username, String password) = 0;
      virtual void disconnect(void) = 0;
      virtual bool is_connected(void) = 0;

    public:
      virtual bool publish(String topic, String message) = 0;

    public:
      virtual void process(void) = 0;
  };

};