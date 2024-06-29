// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

// Serial port baud rate
#define SERIAL_BAUD_RATE 115200

// pinout definition
#define PIN_PH_SENSOR A4
#define PIN_TDS_SENSOR A5
#define PIN_WATER_LOW_SENSOR 2
#define PIN_WATER_HIGH_SENSOR 3

// sensor reading frequency (Hz)
#define SENSORS_SAMPLING_RATE 1000

// MQTT
#define MQTT_PUBLISH_PERIOD 2000 // in ms
#define MQTT_CLIENT_NAME "arduino"
#define MQTT_BROKER "192.168.2.41"
#define MQTT_PORT 1833
#define MQTT_TOPIC_MEASUREMENTS_PH "measurements/ph"
#define MQTT_TOPIC_MEASUREMENTS_TDS "measurements/tds"
#define MQTT_TOPIC_MEASUREMENTS_WATER_LOW "measurements/water_low"
#define MQTT_TOPIC_MEASUREMENTS_WATER_HIGH "measurements/water_high"
#define MQTT_TOPIC_MEASUREMENTS_WATER_LEVEL "measurements/water_level"
#define MQTT_TOPIC_STATUS_WIFI_SIGNAL_STRENGTH "status/wifi_signal_strength"
#define MQTT_TOPIC_STATUS_TIME "status/time"

// RTC
#define RTC_TIMEZONE 2