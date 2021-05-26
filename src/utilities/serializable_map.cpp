#include "serializable_map.h"

namespace CDEM {

  SerializableMap::SerializableMap(void) { }

  // Copy constructor
  SerializableMap::SerializableMap(const SerializableMap &original) {
    for (std::map<String, DataBlock>::const_iterator it = original.memoryMap.begin(); it != original.memoryMap.end(); it++) {
      this->add(it->first, (it->second).memory, (it->second).length);
    }
  }

  // Assignment operator
  SerializableMap& SerializableMap::operator=(const SerializableMap &right) {
    if (this != &right) {     // protect against invalid self-assignment
      this->clear();    // Remove all previous items
      for (std::map<String, DataBlock>::const_iterator it = right.memoryMap.begin(); it != right.memoryMap.end(); it++) {
        this->add(it->first, (it->second).memory, (it->second).length);
      }
    }
    return *this;
  }

  bool SerializableMap::add(String key, const void * data, size_t length) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);

    void * memoryBlock = nullptr;
    if (it != memoryMap.end()) memoryBlock = realloc(memoryMap[key].memory, length);
    else memoryBlock = malloc(length);

    if (!memoryBlock) return false;

    memcpy(memoryBlock, data, length);
    memoryMap[key] = DataBlock({ memoryBlock, length });

    return true;
  }

  void * SerializableMap::get(String key) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);
    if (it == memoryMap.end()) return nullptr;
    return (it->second).memory;
  }

  void SerializableMap::remove(String key) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);
    if (it == memoryMap.end()) return;

    free((it->second).memory);
    memoryMap.erase(it);
  }

  void SerializableMap::clear(void) {
    for (std::map<String, DataBlock>::iterator it = memoryMap.begin(); it != memoryMap.end(); it++) {
      free((it->second).memory);
      (it->second).memory = nullptr;
    }
    memoryMap.clear();
  }

  SerializableMap::~SerializableMap(void) {
    clear();
  }

  size_t SerializableMap::size(void) {
    size_t requiredSize = 0;
    for (std::map<String, DataBlock>::iterator it = memoryMap.begin(); it != memoryMap.end(); it++) {
      requiredSize += (it->first).length()+1;
      requiredSize += sizeof(size_t);
      requiredSize += (it->second).length;
    }

    return requiredSize;
  }

  size_t SerializableMap::serialize(char * buffer, size_t bufferSize) {
    if (bufferSize < size()) return -1;

    // Mapping:
    // KEY\0   DATA_SIZE (4 bytes = sizeof(size_t))   DATA 

    char * pBuffer = buffer;
    for (std::map<String, DataBlock>::iterator it = memoryMap.begin(); it != memoryMap.end(); it++) {

      // Copy the key
      strcpy(pBuffer, (it->first).c_str());
      pBuffer += (it->first).length() + 1;    // +1 for \0

      // Copy data length
      *((size_t*)pBuffer) = (it->second).length;
      pBuffer += sizeof(size_t);

      // Copy data
      memcpy(pBuffer, (it->second).memory, (it->second).length);
      pBuffer += (it->second).length;
    }

    return (pBuffer - buffer);
  }

  size_t SerializableMap::deserialize(const char * buffer, size_t configSize) {
    const char * pBuffer = buffer;

    while ((pBuffer - buffer) < configSize) {
      String key = String(pBuffer);   // Should create String from start to \0
      pBuffer += key.length() + 1;

      size_t length = *((size_t*)pBuffer);
      pBuffer += sizeof(size_t);

      const void * dataStart = pBuffer;
      pBuffer += length;

      add(key, dataStart, length);
    }

    return (pBuffer - buffer);
  }

};