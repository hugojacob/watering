// Copyright (C) 2024, Hugo Drumond Jacob.
//
// SPDX-License-Identifier: Apache-2.0

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <RTC.h>

#include "conf.h"

WiFiUDP Udp;
NTPClient timeClient(Udp);

void rtc_init() {
  RTC.begin();
  timeClient.begin();
  timeClient.update();
  
  auto unixTime = timeClient.getEpochTime() + (RTC_TIMEZONE * 3600);
  RTCTime timeToSet = RTCTime(unixTime);
  RTC.setTime(timeToSet);
}
time_t rtc_get_unix_time() {
  RTCTime currentTime;
  RTC.getTime(currentTime);
  return currentTime.getUnixTime();
}