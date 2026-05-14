#include "globals.h"

WebServer server(80);
Preferences preferences;

RelayState relays[4];
ClimateData climate;
WarningState warningState = WARNING_NONE;
AutomationSettings automationSettings;
