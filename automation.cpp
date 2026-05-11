#include "automation.h"

#include "rtc_manager.h"
#include "relay_manager.h"

#include "config_manager.h"

static bool lightLastState = false;
static bool auxLastState = false;

static bool fogCycleActive = false;

static unsigned long fogCycleStart = 0;

static unsigned long fogLastRun = 0;

void handleLightScheduler()
{
    if (!isRTCValid())
        return;

    if (!getRelayAutoMode(2))
        return;

    int hour = getCurrentHour();

    bool shouldLightBeOn =
        (hour >= lightConfig.onHour &&
        hour < lightConfig.offHour);

    if (shouldLightBeOn != lightLastState)
    {
        lightLastState = shouldLightBeOn;

        setRelay(2, shouldLightBeOn, SOURCE_AUTOMATION);
    }
}

void handleFogScheduler()
{
    if (!isRTCValid())
        return;

    if (!getRelayAutoMode(0))
        return;

    int currentMinutes =
        getCurrentHour() * 60;

    int startMinutes =
        fogConfig.startHour * 60;

    int endMinutes =
        fogConfig.stopHour * 60;

    bool fogWindowActive =
        currentMinutes >= startMinutes &&
        currentMinutes < endMinutes;

    unsigned long currentMillis = millis();

    if (fogLastRun == 0)
{
    fogLastRun =
        currentMillis -
        (fogConfig.intervalHours * 3600000UL);
}

    if (fogWindowActive)
    {
        if (!fogCycleActive)
        {
            unsigned long intervalMs =
                fogConfig.intervalHours * 3600000UL;

            if (currentMillis - fogLastRun >= intervalMs)
            {
                setRelay(
                    0,
                    true,
                    SOURCE_AUTOMATION
                );

                fogCycleActive = true;

                fogCycleStart = currentMillis;

                fogLastRun = currentMillis;
            }
        }

        if (fogCycleActive)
        {
            unsigned long durationMs =
                fogConfig.durationSeconds * 1000UL;

            if (currentMillis - fogCycleStart >= durationMs)
            {
                setRelay(
                    0,
                    false,
                    SOURCE_AUTOMATION
                );

                fogCycleActive = false;
            }
        }
    }
    else
    {
        if (fogCycleActive)
        {
            setRelay(
                0,
                false,
                SOURCE_AUTOMATION
            );

            fogCycleActive = false;
        }
    }
}

void handleAuxScheduler()
{
    if (!isRTCValid())
        return;

    if (!getRelayAutoMode(3))
        return;

    int hour = getCurrentHour();

    bool shouldAuxBeOn =
        (hour >= auxConfig.onHour &&
        hour < auxConfig.offHour);

    if (shouldAuxBeOn != auxLastState)
    {
        auxLastState = shouldAuxBeOn;

        setRelay(3, shouldAuxBeOn, SOURCE_AUTOMATION);
    }
}

void handleAutomation()
{
    handleLightScheduler();

    handleFogScheduler();

    handleAuxScheduler();
}
