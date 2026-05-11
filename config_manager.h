#pragma once

#include <Arduino.h>

struct LightConfig
{
    int onHour;
    int offHour;
};

struct FogConfig
{
    int startHour;
    int stopHour;

    int intervalHours;
    int durationSeconds;
};

struct AuxConfig
{
    int onHour;
    int offHour;
};

extern LightConfig lightConfig;
extern FogConfig fogConfig;
extern AuxConfig auxConfig;

void initConfigs();