#include "configuration_validator.h"
#include "../validators/string_validator.h"
#include "../validators/number_validator.h"
#include "../validators/ip_validator.h"
#include "../validators/mqtt_topic_validator.h"

namespace CDEM {

  String ConfigurationValidator::validate_ssid(String ssid) {
    StringValidator validator(false, 100);
    validator.is_valid(ssid, "SSID");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_password(String password) {
    StringValidator validator(false, 100);
    validator.is_valid(password, "Password");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_dhcp(String dhcp) {
    NumberValidator validator(0, 1);
    validator.is_valid(dhcp, "DHCP");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_static_ip(String ip) {
    IpValidator validator;
    validator.is_valid(ip, "Static IP");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_subnet_mask(String mask) {
    IpValidator validator;
    validator.is_valid(mask, "Subnet Mask");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_gateway_ip(String gw) {
    IpValidator validator;
    validator.is_valid(gw, "Gateway IP");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_broker_ip(String ip) {
    IpValidator validator;
    validator.is_valid(ip, "Broker IP");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_broker_port(String port) {
    NumberValidator validator(1, 65535);
    validator.is_valid(port, "Broker Port");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_mqtt_topic(String topic) {
    MqttTopicValidator validator;
    validator.is_valid(topic, "MQTT Topic");
    return validator.validation_error();
  }

  String ConfigurationValidator::validate_read_period(String period) {
    NumberValidator validator(1, 3600);
    validator.is_valid(period, "Read Period");
    return validator.validation_error();
  }


};