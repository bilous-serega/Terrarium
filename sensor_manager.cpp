#include "sensor_manager.h"

static float currentTemperature = 0.0;
static float currentHumidity = 0.0;

static bool sensorValid = false;

void initSensors()
{
    sensorValid = false;

    currentTemperature = 0.0;
    currentHumidity = 0.0;
}

void updateSensors()
{
    // Placeholder
    // Real sensor logic later
}

bool isSensorValid()
{
    return sensorValid;
}

float getTemperature()
{
    return currentTemperature;
}

float getHumidity()
{
    return currentHumidity;
}