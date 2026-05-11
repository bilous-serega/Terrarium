#pragma once

#include <Arduino.h>

void initWiFi();
void handleWiFi();

bool isWiFiConnected();

String getWiFiIP();
