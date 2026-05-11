#include <Arduino.h>

#include "pins.h"
#include "globals.h"
#include "relay_manager.h"

static const uint8_t relayPins[4] =
{
    PIN_RELAY_1,
    PIN_RELAY_2,
    PIN_RELAY_3,
    PIN_RELAY_4
};

static const char* defaultNames[4] =
{
    "FOG",
    "FAN",
    "LIGHT",
    "AUX"
};

static const unsigned long RELAY_SWITCH_DELAY = 5000;

void initRelays()
{
    for (int i = 0; i < 4; i++)
    {
        relays[i].pin = relayPins[i];
        relays[i].name = defaultNames[i];

        // SAFE DEFAULTS
        relays[i].state = false;

        pinMode(relays[i].pin, OUTPUT);

        // Safe startup state
        digitalWrite(relays[i].pin, HIGH);
    }
}

void setRelay(
    uint8_t index,
    bool state,
    RelaySource source
)
{
    if (index >= 4)
        return;

    unsigned long now = millis();

    if (now - relays[index].lastSwitchTime < RELAY_SWITCH_DELAY)
        return;

    relays[index].lastSwitchTime = now;

    relays[index].state = state;

    relays[index].source = source;

    bool outputState = state;

    if (relays[index].invert)
        outputState = !outputState;

    digitalWrite(relays[index].pin, outputState);
}

bool getRelay(uint8_t index)
{
    if (index >= 4)
        return false;

    return relays[index].state;
}

void setRelayAutoMode(uint8_t index, bool enabled)
{
    if (index >= 4)
        return;

    relays[index].autoMode = enabled;
}

bool getRelayAutoMode(uint8_t index)
{
    if (index >= 4)
        return false;

    return relays[index].autoMode;
}

void setRelayInvert(uint8_t index, bool enabled)
{
    if (index >= 4)
        return;

    relays[index].invert = enabled;

    updateRelayHardware();
}

bool getRelayInvert(uint8_t index)
{
    if (index >= 4)
        return false;

    return relays[index].invert;
}

void setRelayName(uint8_t index, const String& name)
{
    if (index >= 4)
        return;

    relays[index].name = name;
}

void updateRelayHardware()
{
    for (int i = 0; i < 4; i++)
    {
        bool outputState = relays[i].state;

        if (relays[i].invert)
            outputState = !outputState;

        digitalWrite(
            relays[i].pin,
            outputState
        );
    }
}
