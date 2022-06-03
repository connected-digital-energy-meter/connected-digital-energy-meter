#include "pub_sub_publisher.h"
#include "../logging/logger.h"

namespace CDEM {

  PubSubPublisher::PubSubPublisher(WiFiClient &wifiClient) 
    : wifiClient(wifiClient) {
  }

  PubSubPublisher::~PubSubPublisher(void) {
    destroy_client();
  }

  void PubSubPublisher::connect(String broker, unsigned int port, String username, String password) {
    this->broker = broker;
    this->port = port;
    this->username = username;
    this->password = password;
    connect();
  }

  void PubSubPublisher::disconnect(void) {
    client->disconnect();
  }

  bool PubSubPublisher::is_connected(void) {
    return (client && client->connected());
  }

  bool PubSubPublisher::publish(String topic, String message) {
    if (is_connected() && client->publish(topic.c_str(), message.c_str())) {
      return true;
    }

    DoLog.warning("Cannot publish to MQTT broker. Connection lost or message too long.", "pubsub");
    return false;
  }

  void PubSubPublisher::process(void) {
    if (!is_connected() && ((millis() - lastConnectTry) > RETRY_CONNECT_INTERVAL)) {
      DoLog.warning("PubSubClient is not connected to broker", "pubsub");
      connect();
      lastConnectTry = millis();
    }

    if (is_connected()) client->loop();
  }

  // If connection is lost somewhere underway, the PubSubClient doesn't
  // seem to want to reconnect. That is why we are creating new client in that case.
  void PubSubPublisher::build_client(void) {
    destroy_client();

    client = new PubSubClient(wifiClient);
    client->setServer(broker.c_str(), port);
    if (!client->setBufferSize(CLIENT_BUFFER_SIZE)) {
      DoLog.error("Failed to allocate buffer for MQTT Publisher.", "pubsub");
      delete client;
      client = nullptr;
      return;
    }
    clientId = "CDEM-" + String(random(0xffff), HEX);
  }

  void PubSubPublisher::destroy_client(void) {
    if (client) {
      client->disconnect();
      delete client;
      client = nullptr;
    }
  }

  void PubSubPublisher::connect(void) {
    if (is_connected()) {
      DoLog.info("Already connected to broker", "pubsub");
      return;
    }

    DoLog.info("Connecting to broker", "pubsub");
    destroy_client();
    build_client();

    auto mqtt_username = (username == NULL || username == "") ? NULL : username.c_str();
    auto mqtt_password = (password == NULL || password == "") ? NULL : password.c_str();

    if (!client->connect(clientId.c_str(),mqtt_username, mqtt_password, NULL, 0, false, NULL, true)) {
      DoLog.error("Failed to connect to MQTT broker", "pubsub");
      return;
    }

    DoLog.info("Connected to broker", "pubsub");
  }

};