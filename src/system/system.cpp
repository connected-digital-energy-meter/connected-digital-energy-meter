#include "system.h"
#include "../logging/logger.h"
#include "../captive_portal/captive_portal.h"
#include "../config/configuration.h"
#include <Arduino.h>

// Captive Portal
#define CAPTIVE_PORTAL_TIME_WINDOW        300
#define CAPTIVE_PORTAL_SSID               "CDEM-Config"
#define CAPTIVE_PORTAL_PASSWORD           "smartmeter"

namespace CDEM {

  bool System::configure(ConfigurationManager * configManager, DeviceStatus * deviceStatus) {
    // 1. Try loading from EEPROM
    DoLog.info("Loading configuration from EEPROM ...", "system");
    if (!configManager->load_configuration()) {
      DoLog.warning("Configuration load from EEPROM failed. Loading factory defaults", "system");
      configManager->factory_default();
    }

    // 2. Setup configuration portal
    DoLog.info("Setting up Captive Portal for configuration via WiFi", "system");
    CaptivePortal * portal = new CaptivePortal(
      CAPTIVE_PORTAL_SSID,
      CAPTIVE_PORTAL_PASSWORD,
      CAPTIVE_PORTAL_TIME_WINDOW
    );
    portal->start(*configManager->current_config());
    deviceStatus->config_portal_up();

    while (!portal->process());   // Wait for Captive Portal to finish

    DoLog.verbose("Captive Portal finished ...", "system");
    Configuration newConfiguration = portal->resulting_configuration();

    delete portal;

    // 3. Default = no boot; Altered = save to EEPROM
    if (newConfiguration == Configuration()) {
      DoLog.error("Not booting any further until device is properly configured.", "system");
      deviceStatus->not_configured();
      while(true) { delay(1000); }
    } else if (newConfiguration != *(configManager->current_config())) {
      DoLog.verbose("Configuration has been altered via portal. Saving new config to EEPROM ...", "system");
      configManager->current_config(newConfiguration);
      if (configManager->save_configuration()) {
        DoLog.info("Successfully saved new configuration to EEPROM", "system");
      }   // What on fail ?
    }

    return true;
  }

};