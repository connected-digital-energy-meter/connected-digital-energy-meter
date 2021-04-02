#pragma once

#include <Arduino.h>

namespace CDEM {

  class Logger final {

    public:
      enum class LogLevel {
        VERBOSE,
        INFO,
        WARNING,
        ERROR
      };

    public:
      static Logger& get_instance();

    public:
      void set_destination(Stream * stream);
      void set_level(LogLevel level);

    public:
      void verbose(String message, String module = "");
      void info(String message, String module = "");
      void warning(String message, String module = "");
      void error(String message, String module = "");

      // Dont forget to declare these two. You want to make sure they
      // are unacceptable otherwise you may accidentally get copies of
      // your singleton appearing.
    public:
      Logger(Logger const&)          = delete;
      void operator=(Logger const&)  = delete;
      // Note: Scott Meyers mentions in his Effective Modern
      //       C++ book, that deleted functions should generally
      //       be public as it results in better error messages
      //       due to the compilers behavior to check accessibility
      //       before deleted status

    private:
      Logger(void);   // Make constructor private

    private:
      String level_to_string(LogLevel level);
      void log(String message, String module, LogLevel level);

    private:
      Stream * destinationStream = nullptr;
      LogLevel logLevel = LogLevel::VERBOSE;
  };

  #define DoLog Logger::get_instance()
};