#include "pub_sub_publisher.h"
#include "../logging/logger.h"

namespace CDEM {

  PubSubPublisher::PubSubPublisher(WiFiClient &wifiClient) 
    : client(wifiClient) {
  }

  void PubSubPublisher::connect(String broker, unsigned int port) {
    client.setServer(broker.c_str(), port);
    client.setBufferSize(CLIENT_BUFFER_SIZE);
    clientId = "CDEM-";
    clientId += String(random(0xffff), HEX);
    connect();
  }

  void PubSubPublisher::disconnect(void) {
    client.disconnect();
  }

  bool PubSubPublisher::is_connected(void) {
    return client.connected();
  }

  bool PubSubPublisher::publish(String topic, String message) {
    if (is_connected()) {
      return client.publish(topic.c_str(), message.c_str());
    }
    DoLog.warning("Cannot publish. PubSubClient is not connected to broker", "pubsub");
    return false;
  }

  void PubSubPublisher::process(void) {
    if (!is_connected()) {
      DoLog.warning("PubSubClient is not connected to broker", "pubsub");
      connect();
    }

    client.loop();
  }

  void PubSubPublisher::connect(void) {
    DoLog.info("Connecting to broker", "pubsub");
    client.connect(clientId.c_str());
  }

};