#include "configuration.h"

namespace CDEM {

  bool Configuration::add(String key, const void * data, size_t length) {
    std::map<String, DataBlock>::iterator it = memoryMap.find(key);

    void * memoryBlock = nullptr;
    if (it != memoryMap.end()) {
      memoryBlock = realloc(memoryMap[key].memory, length);
      if (memoryBlock) totalSize -= memoryMap[key].length;
    }
    else memoryBlock = malloc(length);

    if (!memoryBlock) return false;

    memcpy(memoryBlock, data, length);
    memoryMap[key] = DataBlock({ memoryBlock, length });
    totalSize += length;

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
    totalSize = 0;
  }

  size_t Configuration::size() {
    return totalSize;
  }

};