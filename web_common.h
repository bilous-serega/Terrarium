#pragma once

#include <Arduino.h>

String buildNavigation();
String buildPageStart(const String& title);
String buildPageEnd();

String relayModeText(bool mode);
String relayStateText(bool state);