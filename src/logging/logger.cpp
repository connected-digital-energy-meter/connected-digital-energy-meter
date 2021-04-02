#include "logger.h"

namespace CDEM {

  Logger& Logger::get_instance() {
    static Logger instance;   // Guaranteed to be destroyed.
    return instance;
  }

  Logger::Logger(void) { }

  void Logger::set_destination(Stream * stream) {
    destinationStream = stream;
  }

  void Logger::set_level(LogLevel level) {
    this->logLevel = level;
  }

  void Logger::verbose(String message, String module) {
    log(message, module, LogLevel::VERBOSE);
  }

  void Logger::info(String message, String module) {
    log(message, module, LogLevel::INFO);
  }

  void Logger::warning(String message, String module) {
    log(message, module, LogLevel::WARNING);
  }

  void Logger::error(String message, String module) {
    log(message, module, LogLevel::ERROR);
  }

  String Logger::level_to_string(LogLevel level) {
    switch (level) {
      case LogLevel::VERBOSE: return "VERBOSE";
      case LogLevel::INFO: return "INFO";
      case LogLevel::WARNING: return "WARNING";
      case LogLevel::ERROR: return "ERROR";
    }
  }

  void Logger::log(String message, String module, LogLevel level) {
    if (destinationStream && level >= logLevel) {
      destinationStream->println(
        "[" + level_to_string(level) + "]"
        + (module != "" ? "(" + module + ") " : " ")
        + message
      );
    }
  }

};