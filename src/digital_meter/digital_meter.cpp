#include "digital_meter.h"
#include "crc_helper.h"
#include "../logging/logger.h"

namespace CDEM {

  DigitalMeter::DigitalMeter(int requestPin, Stream * serial) {
    this->requestPin = requestPin;
    this->serial = serial;
    pinMode(requestPin, OUTPUT);
    disable();
  }

  void DigitalMeter::enable(void) {
    DoLog.verbose("Enabling the digital meter data request", "digital-meter");
    reset_read_state();
    digitalWrite(requestPin, HIGH);
    startTimeoutMillis = millis();
  }

  void DigitalMeter::disable(void) {
    DoLog.verbose("Disabling the digital meter data request", "digital-meter");
    digitalWrite(requestPin, LOW);
  }

  // Read a new datagram from the P1 port
  DigitalMeter::MeterStatus DigitalMeter::read_datagram(char * buffer, size_t bufferLength) {
    if (millis() - startTimeoutMillis > TIMEOUT_MS) {
      DoLog.verbose("Meter timed out", "digital-meter");
      return MeterStatus::TIMED_OUT;
    }

    if (serial->available() > 0) {
      // Get next byte for the P1 port
      char incomingByte = serial->read();
            
      // Look for the start of the datagram
      if (incomingByte == '/') {
        DoLog.verbose("Detected start of a datagram", "digital-meter");
        clear_buffer(buffer, bufferLength);
        reset_read_state();
        startDetected = true;
      }

      // Ignore all data on serial port if start was not detected
      if (startDetected) {
        buffer[readPointer++] = incomingByte;

        // Look for the end of the datagram
        if (incomingByte == '\n' && buffer[readPointer-7] == '!') {
          DoLog.verbose("Read in full datagram", "digital-meter");
          startDetected = false;
          buffer[readPointer] = '\0';   // Null-terminate buffer

          DoLog.verbose(String(buffer), "digital-meter");

          if (CrcHelper::check_crc(buffer, readPointer)) {
            DoLog.verbose("Datagram is valid (CRC check passed)", "digital-meter");
            return MeterStatus::DATAGRAM_READY;
          } else {
            DoLog.warning("Datagram is invalid (CRC check failed)", "digital-meter");
            return MeterStatus::CRC_ERROR;
          }

        } else if (readPointer >= bufferLength) {    // End of datagram not found
          DoLog.warning("Datagram is invalid (could not detect END)", "digital-meter");
          clear_buffer(buffer, bufferLength);
          reset_read_state();
          // Keep reading as long as timeout does not occur
        }
      }
    }

    return MeterStatus::IN_PROGRESS;
  }

  void DigitalMeter::reset_read_state(void) {
    readPointer = 0;
    startDetected = false;
  }

  void DigitalMeter::clear_buffer(char * buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
      buffer[i] = 0;
    }
  }

};