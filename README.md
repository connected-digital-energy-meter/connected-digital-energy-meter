# Connected Digital Energy Meter for Arduino

A library for connecting a Belgian digital energy meter to your home automation system via MQTT.

This library is part of the Connected Digital Energy Meter project. Check it out at [https://connected-digital-energy-meter.netlify.app](https://connected-digital-energy-meter.netlify.app).

## Configuration Page

Access via [http://172.16.10.1](http://172.16.10.1) or scan the QR code below.

![QR Code Configuration Page](./img/qr_configuration_page.png)

## Dependencies

### The CDEM Library

The firmware for the ESP12 module you downloaded is only the tip of the iceberg. Most of the functionality of the firmware is provided by the `Connected Digital Energy Meter` library.

Download the latest release of the [Connected Digital Energy Meter library](https://github.com/connected-digital-energy-meter/connected-digital-energy-meter/releases) as a zip file and include it via `Sketch => Include Library => Add ZIP Library ...`.

### The PubSubClient Library

PubSubClient is a client library for MQTT messaging.

1. Open the Arduino Library Manager via `Tools => Manage Libraries`
2. Search for `PubSubClient` (make sure to use the library by **Nick O'Leary**)
3. Select the version: `2.8.0`
4. Click install.

### The ArduinoJson Library

The ArduinoJson library allows easy parsing and conversion of JSON strings. The full payload of all the meter telemetry is transmitted as JSON.

1. Open the Arduino Library Manager via `Tools => Manage Libraries`
2. Search for `ArduinoJson` (make sure to use the library by **Benoit Blanchon**)
3. Select the version: `6.18.0`
4. Click install.
