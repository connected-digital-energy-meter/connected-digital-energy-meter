#pragma once

#include <Arduino.h>
#include <map>

namespace CDEM {

  class SerializableMap {

    private:
      struct DataBlock {
        void * memory;
        size_t length;
      };

    public:
      SerializableMap(void);
      SerializableMap(const SerializableMap &original);   // Copy constructor
    
    public:
      SerializableMap& operator=(const SerializableMap &t);   // Assignment operator

    public:
      bool add(String key, const void * data, size_t length);
      void * get(String key) const;
      void remove(String key);
      void clear(void);

    public:
      size_t size(void) const;
      size_t serialize(char * buffer, size_t bufferSize) const;
      size_t deserialize(const char * buffer, size_t configSize);

    public:
      ~SerializableMap(void);

    private:
      std::map<String, DataBlock> memoryMap;
  };

};