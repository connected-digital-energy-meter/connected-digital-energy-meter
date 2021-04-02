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

    public:
      size_t size(void);
      // size_t serialize(char * buffer, size_t bufferSize);
      // size_t deserialize(const char * buffer, size configSize);

    public:
      ~Configuration(void);

    private:
      std::map<String, DataBlock> memoryMap;

  };

};




