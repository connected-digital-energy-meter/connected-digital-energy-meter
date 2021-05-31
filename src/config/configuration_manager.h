#pragma once

#include "configuration.h"

namespace CDEM {

  class ConfigurationManager {

    public:
      ConfigurationManager(uint16_t identifier, size_t eepromSize=512);

    public:
      bool load_configuration(void);
      bool save_configuration(void);
      void factory_default(void);

    public:
      void current_config(Configuration config);
      const Configuration * current_config(void) const;

    private:
      void initialize_eeprom(void);

    private:
      void write_identifier(void);
      uint16_t read_identifier(void);

    private:
      size_t eepromSize = 512;
      bool eepromInitialized = false;
      uint16_t configId = 0x0000;

      Configuration _currentConfig;
  };

};