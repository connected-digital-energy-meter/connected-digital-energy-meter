#include "configuration.h"
#include "factory_defaults.h"

namespace CDEM {

  Configuration::Configuration(void) {
    wifi_ssid(WIFI_DEFAULT_SSID);
    wifi_password(WIFI_DEFAULT_PASSWORD);
    mqtt_broker(MQTT_DEFAULT_BROKER);
    mqtt_port(MQTT_DEFAULT_PORT);
    mqtt_username(MQTT_DEFAULT_USERNAME);
    mqtt_password(MQTT_DEFAULT_PASSWORD);
    mqtt_topic(MQTT_DEFAULT_TOPIC);
    use_dhcp(NETWORK_USE_DHCP);
    static_ip(NETWORK_DEFAULT_IP);
    default_gateway(NETWORK_DEFAULT_GATEWAY);
    subnet_mask(NETWORK_DEFAULT_SUBNET);
    read_period(METER_DEFAULT_READ_PERIOD);
  }

  void Configuration::wifi_ssid(String ssid) {
    datamap.add("wifi_ssid", (void*)(ssid.c_str()), ssid.length()+1);
  }

  String Configuration::wifi_ssid(void) const {
    return String((char*)datamap.get("wifi_ssid"));
  }

  void Configuration::wifi_password(String password) {
    datamap.add("wifi_pass", (void*)(password.c_str()), password.length()+1);
  }

  String Configuration::wifi_password(void) const {
    return String((char*)datamap.get("wifi_pass"));
  }

  void Configuration::mqtt_broker(String broker) {
    datamap.add("mqtt_broker", (void*)(broker.c_str()), broker.length()+1);
  }

  String Configuration::mqtt_broker(void) const {
    return String((char*)datamap.get("mqtt_broker"));
  }

  void Configuration::mqtt_port(int port) {
    datamap.add("mqtt_port", (void*)(&port), sizeof(int));
  }

  int Configuration::mqtt_port(void) const {
    return *(int*)datamap.get("mqtt_port");
  }

  void Configuration::mqtt_username(String username) {
    datamap.add("mqtt_username", (void*)(username.c_str()), username.length()+1);
  }

  String Configuration::mqtt_username(void) const {
    return String((char*)datamap.get("mqtt_username"));
  }

  void Configuration::mqtt_password(String password) {
    datamap.add("mqtt_password", (void*)(password.c_str()), password.length()+1);
  }

  String Configuration::mqtt_password(void) const {
    return String((char*)datamap.get("mqtt_password"));
  }
  
  void Configuration::mqtt_topic(String topic) {
    datamap.add("mqtt_topic", (void*)(topic.c_str()), topic.length()+1);
  }

  String Configuration::mqtt_topic(void) const {
    return String((char*)datamap.get("mqtt_topic"));
  }
  
  void Configuration::use_dhcp(bool useDhcp) {
    datamap.add("dhcp", (void*)(&useDhcp), sizeof(bool));
  }

  bool Configuration::use_dhcp(void) const {
    return *(bool*)datamap.get("dhcp");
  }
    
  void Configuration::static_ip(String ip) {
    datamap.add("ip", (void*)(ip.c_str()), ip.length()+1);
  }

  String Configuration::static_ip(void) const {
    return String((char*)datamap.get("ip"));
  }
  
  void Configuration::subnet_mask(String mask) {
    datamap.add("mask", (void*)(mask.c_str()), mask.length()+1);
  }

  String Configuration::subnet_mask(void) const {
    return String((char*)datamap.get("mask"));
  }
  
  void Configuration::default_gateway(String gateway) {
    datamap.add("gw", (void*)(gateway.c_str()), gateway.length()+1);
  }

  String Configuration::default_gateway(void) const {

    return String((char*)datamap.get("gw"));
  }
  
  void Configuration::read_period(unsigned int period) {
    datamap.add("period", (void*)(&period), sizeof(unsigned int));
  }

  unsigned int Configuration::read_period(void) const {
    return *(unsigned int*)datamap.get("period");
  }

  String Configuration::to_string(void) const {
    String output = "";
    output += "WiFi SSID:       " + wifi_ssid() + "\n";
    output += "WiFi Password:   " + wifi_password() + "\n";
    output += "Use DHCP?:       " + String(use_dhcp() ? "yes" : "no") + "\n";
    output += "Static IP:       " + static_ip() + "\n";
    output += "Subnet Mask:     " + subnet_mask() + "\n";
    output += "Default Gateway: " + default_gateway() + "\n";
    output += "MQTT Broker:     " + mqtt_broker() + "\n";
    output += "MQTT Port:       " + String(mqtt_port()) + "\n";
    output += "MQTT Username:   " + mqtt_username() + "\n";
    output += "MQTT Password:   " + mqtt_password() + "\n";
    output += "MQTT Topic:      " + mqtt_topic() + "\n";
    output += "Read period:     " + String(read_period()) + " seconds";
    return output;
  }

  bool Configuration::operator==(const Configuration& rhs) const {
    return (
      wifi_ssid() == rhs.wifi_ssid() &&
      wifi_password() == rhs.wifi_password() &&
      mqtt_broker() == rhs.mqtt_broker() &&
      mqtt_port() == rhs.mqtt_port() &&
      mqtt_username() == rhs.mqtt_username() &&
      mqtt_password() == rhs.mqtt_password() &&
      mqtt_topic() == rhs.mqtt_topic() &&
      use_dhcp() == rhs.use_dhcp() &&
      static_ip() == rhs.static_ip() &&
      subnet_mask() == rhs.subnet_mask() &&
      default_gateway() == rhs.default_gateway() &&
      read_period() == rhs.read_period()
    );
  }

  bool Configuration::operator!=(const Configuration& rhs) const {
    return !(*this == rhs);
  }

  size_t Configuration::serialize(char * buffer, size_t bufferSize) const {
    return datamap.serialize(buffer, bufferSize);
  }

  size_t Configuration::deserialize(const char * buffer, size_t bufferSize) {
    return datamap.deserialize(buffer, bufferSize);
  }

};