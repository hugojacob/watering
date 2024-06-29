// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <FspTimer.h>

typedef void (*timer_callback_t)(timer_callback_args_t*);
bool timer_setup(float rate, timer_callback_t timer_callback);