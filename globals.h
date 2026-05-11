#pragma once

#include <WebServer.h>
#include <Preferences.h>
#include "types.h"

extern WebServer server;
extern Preferences preferences;

extern RelayState relays[4];
extern ClimateData climate;
extern AutomationSettings automationSettings;
