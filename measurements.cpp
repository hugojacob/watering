// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include <debounce.h>

#include "conf.h"

// Useful inline routines
#define UPDATE_BOOL_STATE(pin) [](uint8_t, uint8_t state) { pin = state; }
#define SMOOTH_ANALOG(accumulator, new_reading) accumulator = (accumulator * 0.75) + (new_reading * 0.25)

int tds_value = 0;       // Raw value of the TDS sensor
int ph_value = 0;        // Raw value of the pH sensor
bool water_low = false;  // Status of the "water low" sensor
bool water_high = false; // Status of the "water high" sensor

Button water_low_sensor(PIN_WATER_LOW_SENSOR, UPDATE_BOOL_STATE(water_low));
Button water_high_sensor(PIN_WATER_HIGH_SENSOR, UPDATE_BOOL_STATE(water_high));

void measurements_update_ph() {
  SMOOTH_ANALOG(ph_value, analogRead(PIN_PH_SENSOR));
}
int measurements_get_ph() {
  return ph_value;
}

void measurements_update_tds() {
  SMOOTH_ANALOG(tds_value, analogRead(PIN_TDS_SENSOR));
}
int measurements_get_tds() {
  return tds_value;
}

void measurements_update_water_low() {
  water_low_sensor.update(digitalRead(PIN_WATER_LOW_SENSOR));
}
int measurements_get_water_low() {
  return water_low;
}

void measurements_update_water_high() {
  water_high_sensor.update(digitalRead(PIN_WATER_HIGH_SENSOR));
}
int measurements_get_water_high() {
  return water_high;
}

int measurements_get_tank_status() {
  return (water_high * 2 + water_low) & 0b11;
}