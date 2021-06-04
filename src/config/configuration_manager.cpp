#include "configuration_manager.h"
#include <EEPROM.h>
#include "../logging/logger.h"

namespace CDEM {

  ConfigurationManager::ConfigurationManager(uint16_t identifier, size_t eepromSize) {
    this->eepromSize = eepromSize;
    this->configId = identifier;
    initialize_eeprom();
  }

  bool ConfigurationManager::load_configuration(void) {
    uint16_t id = read_identifier();
    if (id != configId) {
      DoLog.warning("Config identifiers did not match: " + String(id) + " =/= " + String(configId), "config");
      return false;
    }

    char * buffer = new char[eepromSize];

    int offset = sizeof(configId);
    for (uint16_t i = 0; i < eepromSize; i++) {
      buffer[i] = EEPROM.read(offset+i);
    }

    Configuration config;
    size_t actualSize = config.deserialize(buffer, eepromSize);

    delete[] buffer;

    if (!actualSize) {
      DoLog.error("Config deserialization failed.", "config");
      return false;
    }

    _currentConfig = config;

    return true;
  }

  void ConfigurationManager::initialize_eeprom(void) {
    if (!eepromInitialized) {
      EEPROM.begin(eepromSize);
      eepromInitialized = true;
    }
  }

  bool ConfigurationManager::save_configuration(void) {
    if (!eepromInitialized) {
      DoLog.error("Cannot write configuration to EEPROM. Not initialized.", "config");
      return false;
    }

    // Write identifier so we know a config is present in EEPROM
    write_identifier();

    char * buffer = new char[eepromSize];
    size_t actualSize = _currentConfig.serialize(buffer, eepromSize);

    if (!actualSize) {
      DoLog.error("Config serialization failed.", "config");
      return false;
    }

    int offset = sizeof(configId);
    for (int i = 0; i < eepromSize; i++) {
      if (i < actualSize) EEPROM.write(offset+i, buffer[i]);
      else EEPROM.write(offset+i, 0xFF);
    }
  
    delete[] buffer;

    return EEPROM.commit();
  }

  void ConfigurationManager::factory_default(void) {
    _currentConfig = Configuration();
  }

  void ConfigurationManager::current_config(Configuration config) {
    _currentConfig = config;
  }

  const Configuration * ConfigurationManager::current_config(void) const {
    return &_currentConfig;
  }

  void ConfigurationManager::write_identifier(void) {
    EEPROM.write(0, ((configId >> 8) & 0xFF));
    EEPROM.write(1, (configId & 0xFF));
  }

  uint16_t ConfigurationManager::read_identifier(void) {
    return (((uint16_t)EEPROM.read(0)) << 8) + EEPROM.read(1);
  }

};