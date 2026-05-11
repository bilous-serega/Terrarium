#pragma once

#include <Arduino.h>

#include "types.h"

void initRelays();

void setRelay(
    uint8_t index,
    bool state,
    RelaySource source = SOURCE_SYSTEM
);
bool getRelay(uint8_t index);

void setRelayAutoMode(uint8_t index, bool enabled);
bool getRelayAutoMode(uint8_t index);

void setRelayInvert(uint8_t index, bool enabled);
bool getRelayInvert(uint8_t index);

void setRelayName(uint8_t index, const String& name);

void updateRelayHardware();
