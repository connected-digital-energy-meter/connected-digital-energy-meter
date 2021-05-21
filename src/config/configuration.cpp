#include "configuration.h"
#include "factory_defaults.h"

namespace CDEM {

  Configuration::Configuration() {
    wifi_ssid(WIFI_DEFAULT_SSID);
    wifi_password(WIFI_DEFAULT_PASSWORD);
    mqtt_broker(MQTT_DEFAULT_BROKER);
    mqtt_port(MQTT_DEFAULT_PORT);
    mqtt_topic(MQTT_DEFAULT_TOPIC);
    use_dhcp(NETWORK_USE_DHCP);
    static_ip(NETWORK_DEFAULT_IP);
    default_gateway(NETWORK_DEFAULT_GATEWAY);
    subnet_mask(NETWORK_DEFAULT_SUBNET);
    read_period(METER_DEFAULT_READ_PERIOD);
  }

  void Configuration::wifi_ssid(String ssid) {
    this->ssid = ssid;
  }

  String Configuration::wifi_ssid(void) {
    return ssid;
  }

  void Configuration::wifi_password(String password) {
    this->password = password;
  }

  String Configuration::wifi_password(void) {
    return password;
  }

  void Configuration::mqtt_broker(String broker) {
    this->broker = broker;
  }

  String Configuration::mqtt_broker(void) {
    return broker;
  }

  void Configuration::mqtt_port(int port) {
    this->port = port;
  }

  int Configuration::mqtt_port(void) {
    return port;
  }
  
  void Configuration::mqtt_topic(String topic) {
    this->topic = topic;
  }

  String Configuration::mqtt_topic(void) {
    return topic;
  }
  
  void Configuration::use_dhcp(bool useDhcp) {
    this->useDhcp = useDhcp;
  }

  bool Configuration::use_dhcp(void) {
    return useDhcp;
  }
    
  void Configuration::static_ip(String ip) {
    this->ip = ip;
  }

  String Configuration::static_ip(void) {
    return ip;
  }
  
  void Configuration::subnet_mask(String mask) {
    this->netmask = mask;
  }

  String Configuration::subnet_mask(void) {
    return netmask;
  }
  
  void Configuration::default_gateway(String gateway) {
    gw = gateway;
  }

  String Configuration::default_gateway(void) {
    return gw;
  }
  
  void Configuration::read_period(unsigned int period) {
    readPeriod = period;
  }

  unsigned int Configuration::read_period(void) {
    return readPeriod;
  }

  String Configuration::to_string(void) {
    String output = "";
    output += "WiFi SSID:       " + wifi_ssid() + "\n";
    output += "WiFi Password:   " + wifi_password() + "\n";
    output += "Use DHCP?:       " + String(use_dhcp() ? "yes" : "no") + "\n";
    output += "Static IP:       " + static_ip() + "\n";
    output += "Subnet Mask:     " + subnet_mask() + "\n";
    output += "Default Gateway: " + default_gateway() + "\n";
    output += "MQTT Broker:     " + mqtt_broker() + "\n";
    output += "MQTT Port:       " + String(mqtt_port()) + "\n";
    output += "MQTT Topic:      " + mqtt_topic() + "\n";
    output += "Read period:     " + String(read_period()) + " seconds";
    return output;
  }

  // bool Configuration::operator==(const Configuration& rhs) {
  //   return (
  //     wifi_ssid() == rhs.wifi_ssid() &&
  //     wifi_password() == rhs.wifi_password() &&
  //     mqtt_broker() == rhs.mqtt_broker() &&
  //     mqtt_port() == rhs.mqtt_port() &&
  //     mqtt_topic() == rhs.mqtt_topic() &&
  //     use_dhcp() == rhs.use_dhcp() &&
  //     static_ip() == rhs.static_ip() &&
  //     subnet_mask() == rhs.subnet_mask() &&
  //     default_gateway() == rhs.default_gateway() &&
  //     read_period() == rhs.read_period()
  //   );
  // }

  // bool Configuration::operator!=(const Configuration& rhs) {
  //   return !(*this == rhs);
  // }

};