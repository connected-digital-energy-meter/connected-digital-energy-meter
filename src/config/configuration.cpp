#include "configuration.h"

namespace CDEM {

  bool Configuration::add(String key, const void * data, size_t length) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);

    void * memoryBlock = nullptr;
    if (it != memoryMap.end()) memoryBlock = realloc(memoryMap[key].memory, length);
    else memoryBlock = malloc(length);

    if (!memoryBlock) return false;

    memcpy(memoryBlock, data, length);
    memoryMap[key] = DataBlock({ memoryBlock, length });

    return true;
  }

  void * Configuration::get(String key) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);
    if (it == memoryMap.end()) return nullptr;
    return (it->second).memory;
  }

  void Configuration::remove(String key) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);
    if (it == memoryMap.end()) return;

    free((it->second).memory);
    memoryMap.erase(it);
  }

  Configuration::~Configuration(void) {
    for (std::map<String, DataBlock>::iterator it = memoryMap.begin(); it != memoryMap.end(); it++) {
      free((it->second).memory);
      (it->second).memory = nullptr;
    }
    memoryMap.clear();
  }

  size_t Configuration::size(void) {
    size_t requiredSize = 0;
    for (std::map<String, DataBlock>::iterator it = memoryMap.begin(); it != memoryMap.end(); it++) {
      requiredSize += (it->first).length()+1;
      requiredSize += sizeof(size_t);
      requiredSize += (it->second).length;
    }

    return requiredSize;
  }

};