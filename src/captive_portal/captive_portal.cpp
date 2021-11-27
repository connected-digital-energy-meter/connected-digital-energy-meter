#include "captive_portal.h"
#include <ESP8266WiFi.h>
#include "pages/index.h"
#include "pages/success.h"
#include "pages/reset.h"
#include "../logging/logger.h"
#include "../config/configuration_validator.h"

namespace CDEM {

  CaptivePortal::CaptivePortal(String ssid, String password, unsigned int timeWindowSeconds)
    : webServer(WEBSERVER_PORT) {
    this->ssid = ssid;
    this->password = password;
    this->waitTime = 1000*timeWindowSeconds;
  }

  CaptivePortal::~CaptivePortal(void) {
    DoLog.verbose("Stopping webserver", "portal");
    webServer.stop();
    DoLog.verbose("Disconnecting the WiFi AP", "portal");
    WiFi.softAPdisconnect(true);
  }

  bool CaptivePortal::start(Configuration initialConfig) {
    this->newConfig = initialConfig;
    this->initialConfig = initialConfig;

    DoLog.verbose("Starting captive portal with initial config", "portal");
    startTime = millis();

    if (setup_access_point()) {
      DoLog.info("Soft-AP IP address = " + WiFi.softAPIP().toString(), "portal");
      DoLog.verbose("Setting up the dns catch all", "portal");
      setup_dns_server();
      DoLog.verbose("Setting up the webserver", "portal");
      setup_web_server();
      return true;
    }

    return false;   // AP setup failed
  }

  bool CaptivePortal::process(void) {
    static unsigned int stationsConnected = 0;
    static unsigned int cleanupCounter = 5;

    unsigned int newConnected = WiFi.softAPgetStationNum();
    if (stationsConnected < newConnected) {
      DoLog.info("Client connected to AP ...", "portal");
      stationsConnected = newConnected;
    } else if (stationsConnected > newConnected) {
      DoLog.info("Client disconnected from AP ...", "portal");
      stationsConnected = newConnected;
    }

    dnsServer.processNextRequest();
    webServer.handleClient();

    if (!done && idle && (millis() > startTime + waitTime)) {
      DoLog.info("No client requests within portal time window", "portal");
      done = true;
    }

    // Allow webserver to send last reply
    if (done && cleanupCounter > 0) {
      cleanupCounter--;
      delay(20);
      return false;
    }

    return done;
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

  void CaptivePortal::setup_dns_server(void) {
    IPAddress portalIp(172, 16, 10, 1);       // TODO - Refactor

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", portalIp);
  }

  void CaptivePortal::setup_web_server(void) {
    webServer.on("/", [=]() {
      DoLog.info("Getting request for index page", "portal");

      if (this->webServer.method() == HTTP_GET) {
        idle = false;
        DoLog.verbose("Got GET from client", "portal");
        this->webServer.send(200, "text/html", IndexPage::render(&(this->initialConfig)));
      } else if (this->webServer.method() == HTTP_POST) {
        DoLog.verbose("Got POST from client", "portal");

        String errors = parse_config();
        if (errors == "") {
          DoLog.verbose("Configuration is valid", "portal");
          this->webServer.send(200, "text/html", SuccessPage::render());
          done = true;
        } 
        else {
          DoLog.error(errors, "portal");
          this->webServer.send(200, "text/html", IndexPage::render(&(this->newConfig), errors));
        }
      }
    });

    webServer.on("/cancel", [=]() {
      DoLog.info("Getting cancel request", "portal");
      this->webServer.send(200, "text/html", SuccessPage::render());
      done = true;
    });

    webServer.on("/reset", [=]() {
      DoLog.info("Getting factory default request", "portal");
      this->webServer.send(200, "text/html", ResetPage::render());
      newConfig = Configuration();    // Reset to factory defaults
      done = true;
    });

    webServer.onNotFound([=]() {
      DoLog.info("Getting request for unknown route. Redirecting to /", "portal");
      this->webServer.sendHeader("Location", String("/"), true);
      this->webServer.send(302, "text/plain", "");
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

    String password = this->webServer.arg("pass");
    error = ConfigurationValidator::validate_password(password);
    if (error == "") newConfig.wifi_password(password);
    else validationErrors += error + "|";

    String dhcp = this->webServer.arg("dhcp");
    error = ConfigurationValidator::validate_dhcp(dhcp);
    if (error == "") newConfig.use_dhcp((dhcp == "1"));
    else validationErrors += error + "|";

    if (dhcp == "0") {
      String nip = this->webServer.arg("nip");
      error = ConfigurationValidator::validate_static_ip(nip);
      if (error == "") newConfig.static_ip(nip);
      else validationErrors += error + "|";

      String subnet = this->webServer.arg("subnet");
      error = ConfigurationValidator::validate_subnet_mask(subnet);
      if (error == "") newConfig.subnet_mask(subnet);
      else validationErrors += error + "|";

      String gateway = this->webServer.arg("gateway");
      error = ConfigurationValidator::validate_gateway_ip(gateway);
      if (error == "") newConfig.default_gateway(gateway);
      else validationErrors += error + "|";
    }

    String bip = this->webServer.arg("bip");
    error = ConfigurationValidator::validate_broker_ip(bip);
    if (error == "") newConfig.mqtt_broker(bip);
    else validationErrors += error + "|";

    String port = this->webServer.arg("port");
    error = ConfigurationValidator::validate_broker_port(port);
    if (error == "") newConfig.mqtt_port(port.toInt());
    else validationErrors += error + "|";

    String topic = this->webServer.arg("topic");
    error = ConfigurationValidator::validate_mqtt_topic(topic);
    if (error == "") newConfig.mqtt_topic(topic);
    else validationErrors += error + "|";

    String period = this->webServer.arg("period");
    error = ConfigurationValidator::validate_read_period(period);
    if (error == "") newConfig.read_period(period.toInt());
    else validationErrors += error + "|";

    return validationErrors;
  }

};