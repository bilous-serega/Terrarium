#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "globals.h"
#include "display_manager.h"
#include "rtc_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static unsigned long lastDisplayUpdate = 0;

static unsigned long lastPageSwitch = 0;

static int currentPage = 0;

void initDisplay()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
}

void handleDisplay()
{
    if (millis() - lastDisplayUpdate < 2000)
        return;

    lastDisplayUpdate = millis();
    
        if (millis() - lastPageSwitch >= 5000)
        {
            lastPageSwitch = millis();

            currentPage++;

        if (currentPage > 2)
        {
        currentPage = 0;
        }
}

    display.clearDisplay();

    if (warningState != WARNING_NONE)
{
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print("!!! WARNING !!!");

    display.setCursor(0, 20);

    switch (warningState)
    {
        case WARNING_SENSOR_TIMEOUT:
            display.print("SENSOR TIMEOUT");
            break;

        case WARNING_RTC_ERROR:
            display.print("RTC ERROR");
            break;

        default:
            display.print("UNKNOWN");
            break;
    }

    display.display();

    return;
}

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    if (currentPage == 0)
{
    display.setCursor(0, 0);
    display.print("CLIMATE");

    display.setCursor(0, 16);
    display.print("Temp: ");
    display.print(climate.temperature, 1);

    display.setCursor(0, 28);
    display.print("Hum : ");
    display.print(climate.humidity, 1);

    display.setCursor(0, 40);
    display.print("Sensor: ");
    display.print(climate.error);
}

    if (currentPage == 1)
{
    unsigned long seconds = millis() / 1000;

    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;

    display.setCursor(0, 0);
    display.print("SYSTEM");

    display.setCursor(0, 16);
    display.print("Time: ");
    display.print(getTimeString());

    display.setCursor(0, 28);
    display.print("Uptime:");

    display.setCursor(0, 40);
    display.print(hours);
    display.print("h ");
    display.print(minutes);
    display.print("m");

    display.setCursor(0, 52);
    display.print("Heap: ");
    display.print(ESP.getFreeHeap() / 1024);
    display.print("KB");
}

if (currentPage == 2)
{
    display.setCursor(0, 0);
    display.print("RELAYS");

    for (int i = 0; i < 4; i++)
    {
        display.setCursor(0, 16 + (i * 12));

        display.print(relays[i].name);

        display.print(": ");

        display.print(
            relays[i].state ?
            "ON" :
            "OFF"
        );
    }
}

    display.display();
}
