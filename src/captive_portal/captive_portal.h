#pragma once

#include "../config/configuration.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>

namespace CDEM {

  class CaptivePortal {

    public:
      CaptivePortal(String ssid, String password="", unsigned int timeWindowSeconds=60);

    public:
      ~CaptivePortal(void);

    public:
      bool start(Configuration initialConfig);

    public:
      bool process(void);

    public:
      Configuration resulting_configuration(void);

    private:
      bool setup_access_point(void);
      void setup_web_server(void);

    private:
      String parse_config(void);

    private:
      String ssid = "CDEM-Config";
      String password = "";

      unsigned int waitTime = 60;
      unsigned long startTime = 0;
      bool idle = true;           // Got no GET request from user yet
      bool done = false;

      static const unsigned int WEBSERVER_PORT = 80;
      ESP8266WebServer webServer;

      Configuration initialConfig;
      Configuration newConfig;
  };

};