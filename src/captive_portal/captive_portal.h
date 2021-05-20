#pragma once

#include "../config/configuration.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>

namespace CDEM {

  class CaptivePortal {

    public:
      CaptivePortal(String ssid, String password="", unsigned int waitTime=60);

    public:
      bool start(Configuration initialConfig);

    public:
      bool process(void);

    private:
      bool setup_access_point(void);
      void setup_web_server(void);

    private:
      String ssid = "CDEM-Config";
      String password = "";
      unsigned int waitTime = 60;

      static const unsigned int WEBSERVER_PORT = 80;
      ESP8266WebServer webServer;

      Configuration initialConfig;
      Configuration newConfig;
  };

};