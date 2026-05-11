#include <Wire.h>
#include <RTClib.h>

#include <WiFi.h>
#include <time.h>

#include "rtc_manager.h"

RTC_DS3231 rtc;

static int lastSyncDay = -1;

static bool rtcValid = false;

void initRTC()
{
    if (!rtc.begin())
    {
        rtcValid = false;
        return;
    }

    rtcValid = true;

    if (rtc.lostPower())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void syncRTCWithNTP()
{
    if (WiFi.status() != WL_CONNECTED)
        return;

    configTime(
        10800,
        0,
        "pool.ntp.org",
        "time.nist.gov"
    );

    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        return;
    }

    rtc.adjust(
        DateTime(
            timeinfo.tm_year + 1900,
            timeinfo.tm_mon + 1,
            timeinfo.tm_mday,
            timeinfo.tm_hour,
            timeinfo.tm_min,
            timeinfo.tm_sec
        )
    );
}

void handleRTC()
{
    if (!rtcValid)
        return;

    if (WiFi.status() != WL_CONNECTED)
        return;

    int currentHour = getCurrentHour();

    if (currentHour != 0)
        return;

    int currentDay = rtc.now().day();

    if (currentDay == lastSyncDay)
        return;

    syncRTCWithNTP();

    lastSyncDay = currentDay;

    Serial.println("DAILY NTP SYNC");
}

bool isRTCValid()
{
    return rtcValid;
}

String getTimeString()
{
    if (!rtcValid)
        return "--:--:--";

    DateTime now = rtc.now();

    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "%02d:%02d:%02d",
        now.hour(),
        now.minute(),
        now.second()
    );

    return String(buffer);
}

String getDateString()
{
    if (!rtcValid)
        return "--.--.----";

    DateTime now = rtc.now();

    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "%02d.%02d.%04d",
        now.day(),
        now.month(),
        now.year()
    );

    return String(buffer);
}

int getCurrentHour()
{
    if (!rtcValid)
        return 0;

    DateTime now = rtc.now();

    return now.hour();
}

int getCurrentMinute()
{
    if (!rtcValid)
        return 0;

    DateTime now = rtc.now();

    return now.minute();
}
