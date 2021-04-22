#include "configuration.h"

namespace CDEM {

  void Configuration::wifi_ssid(String ssid) {
    datamap.add("wifi_ssid", (void*)(ssid.c_str()), ssid.length()+1);
  }

  String Configuration::wifi_ssid(void) {
    return String((char*)datamap.get("wifi_ssid"));
  }

  void Configuration::wifi_password(String password) {
    datamap.add("wifi_pass", (void*)(password.c_str()), password.length()+1);
  }

  String Configuration::wifi_password(void) {
    return String((char*)datamap.get("wifi_pass"));
  }

  void Configuration::mqtt_broker(String broker) {
    datamap.add("mqtt_broker", (void*)(broker.c_str()), broker.length()+1);
  }

  String Configuration::mqtt_broker(void) {
    return String((char*)datamap.get("mqtt_broker"));
  }

  void Configuration::mqtt_port(int port) {
    datamap.add("mqtt_port", (void*)(&port), sizeof(int));
  }

  int Configuration::mqtt_port(void) {
    return *(int*)datamap.get("mqtt_port");
  }
  
  void Configuration::mqtt_topic(String topic) {
    datamap.add("mqtt_topic", (void*)(topic.c_str()), topic.length()+1);
  }

  String Configuration::mqtt_topic(void) {
    return String((char*)datamap.get("mqtt_topic"));
  }
  
  void Configuration::use_dhcp(bool useDhcp) {
    datamap.add("dhcp", (void*)(&useDhcp), sizeof(useDhcp));
  }

  bool Configuration::use_dhcp(void) {
    return *(bool*)datamap.get("dhcp");
  }
    
  void Configuration::static_ip(String ip) {
    datamap.add("ip", (void*)(ip.c_str()), ip.length()+1);
  }

  String Configuration::static_ip(void) {
    return String((char*)datamap.get("ip"));
  }
  
  void Configuration::subnet_mask(String mask) {
    datamap.add("mask", (void*)(mask.c_str()), mask.length()+1);
  }

  String Configuration::subnet_mask(void) {
    return String((char*)datamap.get("mask"));
  }
  
  void Configuration::default_gateway(String gateway) {
    datamap.add("gw", (void*)(gateway.c_str()), gateway.length()+1);
  }

  String Configuration::default_gateway(void) {

    return String((char*)datamap.get("gw"));
  }
  
  void Configuration::read_period(unsigned int period) {
    datamap.add("period", (void*)(&period), sizeof(unsigned int));
  }

  unsigned int Configuration::read_period(void) {
    return *(unsigned int*)datamap.get("period");
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

  bool Configuration::operator==(const Configuration& rhs) {
    return (
      wifi_ssid() == rhs.wifi_ssid() &&
      wifi_password() == rhs.wifi_password() &&
      mqtt_broker() == rhs.mqtt_broker() &&
      mqtt_port() == rhs.mqtt_port() &&
      mqtt_topic() == rhs.mqtt_topic() &&
      use_dhcp() == rhs.use_dhcp() &&
      static_ip() == rhs.static_ip() &&
      subnet_mask() == rhs.subnet_mask() &&
      default_gateway() == rhs.default_gateway() &&
      read_period() == rhs.read_period()
    );
  }

  bool Configuration::operator!=(const Configuration& rhs) {
    return !(*this == rhs);
  }

};