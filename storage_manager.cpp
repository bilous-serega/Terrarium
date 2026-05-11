#include "globals.h"
#include "storage_manager.h"
#include "config_manager.h"

void initStorage()
{
    preferences.begin("terrarium", false);

    loadSettings();
}

void loadSettings()
{
    // Reserved for future global settings
}

void restoreRelaySettings()
{
    for (int i = 0; i < 4; i++)
    {
        String keyInvert = "inv" + String(i);
        String keyAuto = "auto" + String(i);

        relays[i].invert =
            preferences.getBool(
                keyInvert.c_str(),
                false
            );

        relays[i].autoMode =
            preferences.getBool(
                keyAuto.c_str(),
                true
            );
    }
}

void saveSettings()
{
    for (int i = 0; i < 4; i++)
    {
        String keyInvert = "inv" + String(i);
        String keyAuto = "auto" + String(i);

        preferences.putBool(
            keyInvert.c_str(),
            relays[i].invert
        );

        preferences.putBool(
            keyAuto.c_str(),
            relays[i].autoMode
        );
    }
}

void saveConfigs()
{
    preferences.putInt(
        "light_on",
        lightConfig.onHour
    );

    preferences.putInt(
        "light_off",
        lightConfig.offHour
    );

    preferences.putInt(
        "fog_start",
        fogConfig.startHour
    );

    preferences.putInt(
        "fog_stop",
        fogConfig.stopHour
    );

    preferences.putInt(
        "fog_int",
        fogConfig.intervalHours
    );

    preferences.putInt(
        "fog_dur",
        fogConfig.durationSeconds
    );

    preferences.putInt(
        "aux_on",
        auxConfig.onHour
    );

    preferences.putInt(
        "aux_off",
        auxConfig.offHour
    );
}

void loadConfigs()
{
    lightConfig.onHour =
        preferences.getInt(
            "light_on",
            8
        );

    lightConfig.offHour =
        preferences.getInt(
            "light_off",
            20
        );

    fogConfig.startHour =
        preferences.getInt(
            "fog_start",
            8
        );

    fogConfig.stopHour =
        preferences.getInt(
            "fog_stop",
            20
        );

    fogConfig.intervalHours =
        preferences.getInt(
            "fog_int",
            2
        );

    fogConfig.durationSeconds =
        preferences.getInt(
            "fog_dur",
            30
        );

    auxConfig.onHour =
        preferences.getInt(
            "aux_on",
            10
        );

    auxConfig.offHour =
        preferences.getInt(
            "aux_off",
            22
        );
}
