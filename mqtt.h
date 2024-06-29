// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

void mqtt_init();
void mqtt_poll();
bool mqtt_check();

int mqtt_publish_measurement_ph();
int mqtt_publish_measurement_tds();
bool mqtt_publish_measurement_water_low();
bool mqtt_publish_measurement_water_high();
int mqtt_publish_status_wifi_signal_strength();
unsigned long mqtt_publish_status_unix_time();