#include "config_manager.h"

LightConfig lightConfig;
FogConfig fogConfig;
AuxConfig auxConfig;

void initConfigs()
{
    lightConfig.onHour = 8;
    lightConfig.offHour = 20;

    fogConfig.startHour = 8;
    fogConfig.stopHour = 23;

    fogConfig.intervalHours = 1;
    fogConfig.durationSeconds = 5;

    auxConfig.onHour = 10;
    auxConfig.offHour = 22;
}