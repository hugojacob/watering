// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include "conf.h"
#include "display.h"
#include "measurements.h"
#include "mqtt.h"
#include "rtc.h"
#include "timer.h"
#include "wifi.h"

#define PRINT_DEC(str, value) Serial.print(str); Serial.print(": "); Serial.println(value, DEC)

void timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  measurements_update_ph();
  measurements_update_tds();
  measurements_update_water_low();
  measurements_update_water_high();
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Starting...");

  wifi_setup();

  Serial.println("Setting up digital input pins");
  pinMode(PIN_WATER_LOW_SENSOR, INPUT_PULLUP);
  pinMode(PIN_WATER_HIGH_SENSOR, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Setting up LED matrix");
  display_init();

  Serial.println("Setting up RTC");
  rtc_init();

  Serial.println("Setting timer");
  timer_setup(SENSORS_SAMPLING_RATE, &timer_callback);
}

void loop() {
  if (wifi_check()) {
    //display_draw_wifi(wifi_get_signal_strength());
  } else {
    wifi_setup();
  }

  if (mqtt_check()) {
    mqtt_poll();
    digitalWrite(LED_BUILTIN, HIGH);

    PRINT_DEC(MQTT_TOPIC_MEASUREMENTS_TDS, mqtt_publish_measurement_tds());
    PRINT_DEC(MQTT_TOPIC_MEASUREMENTS_PH, mqtt_publish_measurement_ph());
    PRINT_DEC(MQTT_TOPIC_MEASUREMENTS_WATER_LOW, mqtt_publish_measurement_water_low());
    PRINT_DEC(MQTT_TOPIC_MEASUREMENTS_WATER_HIGH, mqtt_publish_measurement_water_high());
    PRINT_DEC(MQTT_TOPIC_STATUS_WIFI_SIGNAL_STRENGTH, mqtt_publish_status_wifi_signal_strength());
    PRINT_DEC(MQTT_TOPIC_STATUS_TIME, mqtt_publish_status_unix_time());

    display_draw_tank( measurements_get_tank_status());
  } else {
    Serial.println("MQTT disconnected. Reconnecting.");
    digitalWrite(LED_BUILTIN, LOW);
    mqtt_init();
  }

  delay(MQTT_PUBLISH_PERIOD);
}

