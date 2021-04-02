#pragma once

#include <Arduino.h>
#include <map>

namespace CDEM {

  class Configuration {

    private:
      struct DataBlock {
        void * memory;
        size_t length;
      };

    public:
      bool add(String key, const void * data, size_t length);
      void * get(String key);
      void remove(String key);
      size_t size();

    public:
      ~Configuration(void);

    private:
      std::map<String, DataBlock> memoryMap;
      size_t totalSize = 0;

  };

};




