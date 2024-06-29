// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

#include "conf.h"
#include "measurements.h"
#include "rtc.h"
#include "secrets.h"
#include "wifi.h"

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

#define MQTT_PUBLISH_NUM(topic, value) \
  mqttClient.beginMessage(topic); \
  mqttClient.print("{\"value\":"); \
  mqttClient.print(value); \
  mqttClient.print("}"); \
  mqttClient.endMessage();


#define MQTT_PUBLISH_BOOL(topic, value) \
  mqttClient.beginMessage(topic); \
  mqttClient.print("{\"state\":\""); \
  mqttClient.print(value ? "ON" : "OFF"); \
  mqttClient.print("\"}"); \
  mqttClient.endMessage();

void mqtt_init() {
  mqttClient.setId(MQTT_CLIENT_NAME);
  mqttClient.setUsernamePassword(SECRET_MQTT_USER, SECRET_MQTT_PASS);
  if (!mqttClient.connect(MQTT_BROKER, MQTT_PORT)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  } else {
    Serial.print("MQTT connected!");
  }
}

void mqtt_poll() {
  mqttClient.poll();
}

bool mqtt_check() {
  return (bool) mqttClient.connected();
}

int mqtt_publish_measurement_ph() {
  auto value = measurements_get_ph();
  MQTT_PUBLISH_NUM(MQTT_TOPIC_MEASUREMENTS_PH, value);
  return value;
}

int mqtt_publish_measurement_tds() {
  auto value = measurements_get_tds();
  MQTT_PUBLISH_NUM(MQTT_TOPIC_MEASUREMENTS_TDS, value);
  return value;
}

bool mqtt_publish_measurement_water_low() {
  auto value = measurements_get_water_low();
  MQTT_PUBLISH_BOOL(MQTT_TOPIC_MEASUREMENTS_WATER_LOW, value);
  return value;
}

bool mqtt_publish_measurement_water_high() {
  auto value = measurements_get_water_high();
  MQTT_PUBLISH_BOOL(MQTT_TOPIC_MEASUREMENTS_WATER_HIGH, value);
  return value;
}

int mqtt_publish_status_wifi_signal_strength() {
  auto value = wifi_get_signal_strength();
  MQTT_PUBLISH_NUM(MQTT_TOPIC_STATUS_WIFI_SIGNAL_STRENGTH, value);
  return value;
}

unsigned long mqtt_publish_status_unix_time() {
  auto value = rtc_get_unix_time();
  MQTT_PUBLISH_NUM(MQTT_TOPIC_STATUS_TIME, value);
  return value;
}