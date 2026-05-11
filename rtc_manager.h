#pragma once

#include <Arduino.h>

void initRTC();
void handleRTC();

void syncRTCWithNTP();

bool isRTCValid();

String getTimeString();
String getDateString();

int getCurrentHour();
int getCurrentMinute();
