#include "captive_portal.h"
#include <ESP8266WiFi.h>
#include "pages/index.h"
#include "../logging/logger.h"

namespace CDEM {

  CaptivePortal::CaptivePortal(String ssid, String password, unsigned int waitTime)
    : webServer(WEBSERVER_PORT) {
    this->ssid = ssid;
    this->password = password;
    this->waitTime = waitTime;
  }

  bool CaptivePortal::start(Configuration initialConfig) {
    this->newConfig = initialConfig;
    this->initialConfig = initialConfig;

    DoLog.verbose("Starting captive portal with initial config", "portal");

    if (setup_access_point()) {
      DoLog.info("Soft-AP IP address = " + WiFi.softAPIP().toString(), "portal");
      DoLog.verbose("Setting up the webserver", "portal");
      setup_web_server();
      return true;
    }

    return false;   // AP setup failed
  }

  bool CaptivePortal::process(void) {
    webServer.handleClient();

    static unsigned long last = millis();
    if (millis() - last > 1000) {
      last = millis();
      Serial.println("Stations connected = " + String(WiFi.softAPgetStationNum()));
    }

    // TODO - If no client connects within waitTime then return false

    return true;   // Not done yet      // TODO - Return false if configured
  }

  bool CaptivePortal::setup_access_point(void) {
    IPAddress portalIp(172, 16, 10, 1);       // TODO - Use helper here !
    IPAddress gatewayIp(172, 16, 10, 1);      // No Internet required
    IPAddress networkMask(255, 255, 255, 0);

    bool status = WiFi.softAPConfig(portalIp, gatewayIp, networkMask);
    if (status) DoLog.info("Soft-AP configuration ... All good", "portal");
    else DoLog.error("Soft-AP configuration ... Failed", "portal");

    status = status && WiFi.softAP(this->ssid, this->password);
    if (status) DoLog.info("Starting soft-AP ... All good", "portal");
    else DoLog.error("Starting soft-AP ... Failed", "portal");

    return status;
  }

  void CaptivePortal::setup_web_server(void) {
    webServer.on("/", [=]() {
      DoLog.verbose("Getting request for index page", "portal");
      this->webServer.send(200, "text/html", IndexPage::get(&(this->newConfig)));
    });

    webServer.on("/post",[=]() {
      DoLog.verbose("Got POST from client", "portal");

      String wifiSsid = this->webServer.arg("ssid");
      String wifiPass = this->webServer.arg("pass");
      String dhcp = this->webServer.arg("dhcp");
      Serial.print("wifiSSID = "); Serial.println(wifiSsid);
      Serial.print("wifiPass = "); Serial.println(wifiPass);
      Serial.print("dhcp = "); Serial.println(dhcp);

      // TODO - Validate
      // if (ok) send back rebooting ....
      // if (not_oke) send back index page with errors and data
      //this->webServer.send(200, "text/html", IndexPage::post());
    });

    webServer.onNotFound([=]() {
      this->webServer.send(200, "text/html", "Page not Found");
    });

    webServer.begin();
  }

};