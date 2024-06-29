// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include "timer.h"

FspTimer timer;

// This was taken from https://www.pschatzmann.ch/home/2023/07/01/under-the-hood-arduino-uno-r4-timers/
bool timer_setup(float rate, timer_callback_t timer_callback) {
  uint8_t timer_type = GPT_TIMER;
  int8_t tindex = FspTimer::get_available_timer(timer_type);

  if (tindex < 0) {
    tindex = FspTimer::get_available_timer(timer_type, true);
  }

  if (tindex < 0) {
    return false;
  }

  FspTimer::force_use_of_pwm_reserved_timer();

  if(!timer.begin(TIMER_MODE_PERIODIC, timer_type, tindex, rate, 0.0f, timer_callback)){
    return false;
  }

  if (!timer.setup_overflow_irq()) {
    return false;
  }

  if (!timer.open()) {
    return false;
  }

  if (!timer.start()) {
    return false;
  }

  return true;
}