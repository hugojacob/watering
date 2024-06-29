# Watering system

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This is a small system that reads a few sensors (described below) and send
its raw data via MQTT.

The original intention is to integrate it into Home Assistant so that via some
high level logic on Home Assistant a pump can be activated.

## Bill of material

- Arduino Uno R4 WiFi
- 1x TDS Sensor ([CQRSENTDS01](http://www.cqrobot.wiki/index.php/TDS_(Total_Dissolved_Solids)_Meter_Sensor_SKU:_CQRSENTDS01))
- 1x pH Sensor
- 2x Discrete water level sensors (float sensors) ([I have these](https://www.amazon.de/dp/B0B7S2N6B3))

## Connections

These are configurable in `conf.h`.

```
-----------+
           |
   A   A4 -+- pH Sensor
   r       |
   d   A5 -+- TDS sensor
   u       |
   i   D2 -+- Water low sensor
   n       |
   o   D3 -+- Water high sensor
           |
-----------+
```

## Secrets

Enter your WiFi SSID/password as well as the MQTT broker IP address, port and credentials in the `conf.h` file.

----
Copyright (C) 2024, Hugo Drumond Jacob.
