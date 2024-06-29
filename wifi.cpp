// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include <Serial.h>
#include <WiFiS3.h>

#include "secrets.h"
#include "wifi.h"

void wifi_setup() {
  Serial.println("Setting up WiFi...");
  auto wifi_status = WiFi.status();

  if (wifi_status == WL_NO_MODULE) {
    Serial.println("  Communication with WiFi module failed, halting!");
    while (true);
  }

  while (wifi_status != WL_CONNECTED) {
    Serial.print("  Attempting to connect to WPA SSID: "); Serial.println(SECRET_WIFI_SSID);
    wifi_status = WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASS);
    delay(1000);
  }
  Serial.println("  Connected!");
}

bool wifi_check() {
  return (WiFi.status() == WL_CONNECTED);
}

int wifi_get_signal_strength() {
  auto rssi = WiFi.RSSI();
  if(rssi <= -100)
    return 0;

  if(rssi >= -50)
    return 100;

  return 2 * (rssi + 100);
}