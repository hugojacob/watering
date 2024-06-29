// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include <Arduino_LED_Matrix.h>
#include "measurements.h"

ArduinoLEDMatrix matrix;

const uint32_t tank[][3] = 	{
  {0x88a8ee88, 0xa8808888, 0xe888ef80}, // empty
  {0x88a8ee88, 0xa880f88f, 0xe8f8ef80}, // mid
  {0x88afeef8, 0xaf80f88f, 0xe8f8ef80}  // high
};

const uint32_t wifi[][3] = 	{
  {0xaadaa9aa, 0xd529000f, 0xff801fff}, // 0
  {0xaadaa9aa, 0xd529000f, 0xffc01fff}, // 1-10
  {0xaadaa9aa, 0xd529000f, 0xffe01fff}, // 11-20
  {0xaadaa9aa, 0xd529000f, 0xfff01fff}, // 21-30
  {0xaadaa9aa, 0xd529000f, 0xfff81fff}, // 31-40
  {0xaadaa9aa, 0xd529000f, 0xfffc1fff}, // 41-50
  {0xaadaa9aa, 0xd529000f, 0xfffe1fff,}, // 51-60
  {0xaadaa9aa, 0xd529000f, 0xffff1fff,}, // 61-70
  {0xaadaa9aa, 0xd529000f, 0xffff9fff,}, // 71-80
  {0xaadaa9aa, 0xd529000f, 0xffffdfff,}, // 81-90
  {0xaadaa9aa, 0xd529000f, 0xffffffff,}, // 91-100
};

void display_init() {
  matrix.begin();
}

void display_draw_tank(uint8_t type) {
  switch(type) {
    case TANK_STATUS_HIGH:
      matrix.loadFrame(tank[2]);
      break; 
    case TANK_STATUS_ERROR:
      break;
    case TANK_STATUS_MIDDLE:
      matrix.loadFrame(tank[1]);
      break;
    case TANK_STATUS_LOW:
      matrix.loadFrame(tank[0]);
      break;
    default: break;
  }
}

void display_draw_wifi(int strength) {
  auto index = 0;
  if (strength <= 0) {
    index = 0;
  } else if (strength >= 100) {
    index = 10;
  } else {
    index = strength / 11 + 1;
  }
  
  matrix.loadFrame(wifi[index]);
}