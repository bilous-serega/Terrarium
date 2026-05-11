#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "globals.h"
#include "display_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static unsigned long lastDisplayUpdate = 0;

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

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(climate.temperature);

    display.setCursor(0, 10);
    display.print("Hum: ");
    display.print(climate.humidity);

    display.display();
}
