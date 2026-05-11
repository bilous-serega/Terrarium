#include <WiFi.h>

#include "globals.h"
#include "wifi_manager.h"

#include "rtc_manager.h"

static String apSSID = "TerrariumSetup";
static String apPassword = "12345678";

static bool stationConnected = false;
static unsigned long lastReconnect = 0;

static void startAccessPoint()
{
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(
        apSSID.c_str(),
        apPassword.c_str()
    );

    Serial.println("AP STARTED");
    Serial.println(WiFi.softAPIP());
}

static void connectStation()
{
    String ssid =
        preferences.getString("wifi_ssid", "");

    String password =
        preferences.getString("wifi_pass", "");

    if (ssid.length() == 0)
    {
        Serial.println("NO WIFI CONFIG");
        return;
    }

    WiFi.begin(
        ssid.c_str(),
        password.c_str()
    );

    Serial.println("CONNECTING WIFI...");
}

void initWiFi()
{
    WiFi.mode(WIFI_AP_STA);

    startAccessPoint();
    connectStation();
}

void handleWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        if (!stationConnected)
        {
            stationConnected = true;

            Serial.println("WIFI CONNECTED");
            Serial.println(WiFi.localIP());

            syncRTCWithNTP();

            Serial.println("RTC SYNCED WITH NTP");
        }

        return;
    }

    stationConnected = false;

    if (millis() - lastReconnect < 10000)
        return;

    lastReconnect = millis();

    connectStation();
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String getWiFiIP()
{
    if (WiFi.status() == WL_CONNECTED)
        return WiFi.localIP().toString();

    return WiFi.softAPIP().toString();
}
