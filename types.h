#pragma once

#include <Arduino.h>

enum RelaySource
{
    SOURCE_MANUAL,
    SOURCE_AUTOMATION,
    SOURCE_SYSTEM,
    SOURCE_FAILSAFE
};

struct RelayState
{
    bool state = false;
    bool autoMode = true;
    bool invert = false;

    uint8_t pin = 0;

    String name;

    unsigned long lastSwitchTime = 0;

    RelaySource source = SOURCE_SYSTEM;
};

struct ClimateData
{
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool valid = false;
    unsigned long lastUpdate = 0;
};

struct AutomationSettings
{
    float fanOnTemp = 28.0f;
    float fanOffTemp = 26.0f;

    uint32_t fogInterval = 3600000;
    uint32_t fogDuration = 30000;
};
