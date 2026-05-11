#include "globals.h"

#include "relay_manager.h"
#include "storage_manager.h"
#include "rtc_manager.h"
#include "wifi_manager.h"
#include "display_manager.h"
#include "web_server.h"
#include "automation.h"
#include "config_manager.h"
#include "sensor_manager.h"
#include <Wire.h>

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    initStorage();

    initConfigs();
    loadConfigs();

    initRelays();

    restoreRelaySettings();

    initRTC();

    initSensors();

    initWiFi();

    delay(2000);

    initDisplay();

    initWebServer();
}

void loop()
{
    handleWiFi();

    handleRTC();

    updateSensors();

    handleAutomation();

    handleDisplay();

    handleWebServer();
}