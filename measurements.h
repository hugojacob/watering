// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

/*
Tanks status is based on the state of the water low/high sensors.

0 = --    |     1 = -\

Water high | Water low | Tank status
-----------+-----------+--------------
     0     |     0     |  High
     0     |     1     |  Error
     1     |     0     |  Mid
     1     |     1     |  Low
*/
#define TANK_STATUS_HIGH   0b00
#define TANK_STATUS_ERROR  0b01
#define TANK_STATUS_MIDDLE 0b10
#define TANK_STATUS_LOW    0b11

void measurements_update_ph();
int measurements_get_ph();

void measurements_update_tds();
int measurements_get_tds();

void measurements_update_water_low();
bool measurements_get_water_low();

void measurements_update_water_high();
bool measurements_get_water_high();

int measurements_get_tank_status();