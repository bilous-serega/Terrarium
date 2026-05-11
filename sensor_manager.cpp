#include "sensor_manager.h"
#include "pins.h"
#include "globals.h"
#include "config.h"

#include <DHT.h>
#include <math.h>

#define DHT_TYPE DHT22

static DHT dht(PIN_DHT, DHT_TYPE);

static bool sensorValid = false;

static unsigned long lastReadTime = 0;

void initSensors()
{
    dht.begin();

    sensorValid = false;

    climate.temperature = 0.0;
    climate.humidity = 0.0;

    Serial.println("DHT22 INIT");
}

void updateSensors()
{
    if (millis() - lastReadTime < 2000)
        return;

    lastReadTime = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity))
{
    if (millis() - climate.lastUpdate > 10000)
    {
        sensorValid = false;
        climate.valid = false;
    }

#if DEBUG_SENSORS
    Serial.println("DHT READ ERROR");
#endif

    return;
}

    climate.temperature = temperature;
    climate.humidity = humidity;

    climate.valid = true;
    climate.lastUpdate = millis();

        sensorValid = true;

    #if DEBUG_SENSORS
        Serial.print("TEMP: ");
        Serial.println(climate.temperature);

        Serial.print("HUM: ");
        Serial.println(climate.humidity);
    #endif
}

bool isSensorValid()
{
    return sensorValid;
}

float getTemperature()
{
    return climate.temperature;
}

float getHumidity()
{
    return climate.humidity;
}