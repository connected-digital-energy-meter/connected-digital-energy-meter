#include "captive_portal.h"
#include <ESP8266WiFi.h>
#include "pages/index.h"
#include "../logging/logger.h"
#include "../config/configuration_validator.h"

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

    return !done;   // Not done yet      // TODO - Return false if configured
  }

  Configuration CaptivePortal::resulting_configuration(void) {
    return newConfig;
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

      String errors = parse_config();
      if (errors == "") {
        done = true;
        DoLog.verbose("Configuration is valid", "portal");
        this->webServer.send(200, "text/html", "Configuration is ok. Booting the system now ...");
      } 
      else {
        DoLog.error(errors, "portal");
        this->webServer.send(200, "text/html", IndexPage::get(&(this->newConfig), errors));
      }
    });

    webServer.onNotFound([=]() {
      this->webServer.send(200, "text/html", "Page not Found");
    });

    webServer.begin();
  }

  String CaptivePortal::parse_config(void) {
    String validationErrors = "";
    String error = "";

    String ssid = this->webServer.arg("ssid");
    error = ConfigurationValidator::validate_ssid(ssid);
    if (error == "") newConfig.wifi_ssid(ssid);
    else validationErrors += error + "|";

    // String pass = this->webServer.arg("pass");
    // newConfig.wifi_password(pass);

    // // String dhcp = this->webServer.arg("dhcp");
    // // newConfig.use_dhcp(pass);

    // String nip = this->webServer.arg("nip");
    // newConfig.static_ip(nip);

    // String subnet = this->webServer.arg("subnet");
    // newConfig.subnet_mask(subnet);

    // String gateway = this->webServer.arg("gateway");
    // newConfig.default_gateway(gateway);

    // String bip = this->webServer.arg("bip");
    // newConfig.mqtt_broker(bip);

    // // String port = this->webServer.arg("port");
    // // newConfig.mqtt_port(port);

    // String topic = this->webServer.arg("topic");
    // newConfig.mqtt_topic(topic);

    // // String period = this->webServer.arg("period");
    // // newConfig.read_period(period);

    return validationErrors;
  }

};