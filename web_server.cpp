#include "globals.h"
#include "relay_manager.h"
#include "storage_manager.h"
#include "config_manager.h"

#include "web_server.h"

#include "web_dashboard.h"
#include "web_automation.h"
#include "web_hardware.h"
#include "web_wifi.h"

static void redirectHome()
{
    server.sendHeader("Location", "/");
    server.send(303);
}

static void handleRelayOn()
{
    int id = server.arg("id").toInt();

    if (!getRelayAutoMode(id))
    {
        setRelay(id, true, SOURCE_MANUAL);
    }

    redirectHome();
}

static void handleRelayOff()
{
    int id = server.arg("id").toInt();

    if (!getRelayAutoMode(id))
    {
        setRelay(id, false, SOURCE_MANUAL);
    }

    redirectHome();
}

static void handleRelayMode()
{
    int id = server.arg("id").toInt();

    String mode = server.arg("value");

    setRelayAutoMode(id, mode == "auto");

    saveSettings();

    redirectHome();
}

static void handleRelayInvert()
{
    int id = server.arg("id").toInt();

    bool value =
        server.arg("value") == "1";

    relays[id].invert = value;

    updateRelayHardware();

    saveSettings();

    server.sendHeader("Location", "/hardware");
    server.send(303);
}

static void handleSaveLight()
{
    lightConfig.onHour =
        server.arg("on").toInt();

    lightConfig.offHour =
        server.arg("off").toInt();

    saveConfigs();

    server.sendHeader(
        "Location",
        "/automation"
    );

    server.send(303);
}

static void handleSaveFog()
{
    fogConfig.startHour =
        server.arg("start").toInt();

    fogConfig.stopHour =
        server.arg("stop").toInt();

    fogConfig.intervalHours =
        server.arg("interval").toInt();

    fogConfig.durationSeconds =
        server.arg("duration").toInt();

    automationSettings.fogHumidityMin =
        server.arg("hmin").toInt();

    automationSettings.fogHumidityMax =
        server.arg("hmax").toInt();

    saveConfigs();

    saveSettings();

    server.sendHeader(
        "Location",
        "/automation"
    );

    server.send(303);
}

static void handleSaveFan()
{
    automationSettings.fanOnTemp =
        server.arg("on").toInt();

    automationSettings.fanOffTemp =
        server.arg("off").toInt();

    saveSettings();

    server.sendHeader(
        "Location",
        "/automation"
    );

    server.send(303);
}

static void handleSaveAux()
{
    auxConfig.onHour =
        server.arg("on").toInt();

    auxConfig.offHour =
        server.arg("off").toInt();

    saveConfigs();

    server.sendHeader(
        "Location",
        "/automation"
    );

    server.send(303);
}

void initWebServer()
{
    server.on("/", []()
    {
        server.send(
            200,
            "text/html",
            buildDashboardPage()
        );
    });

    server.on("/automation", []()
    {
        server.send(
            200,
            "text/html",
            buildAutomationPage()
        );
    });

    server.on("/hardware", []()
    {
        server.send(
            200,
            "text/html",
            buildHardwarePage()
        );
    });

    server.on("/wifi", []()
    {
        server.send(
            200,
            "text/html",
            buildWiFiPage()
        );
    });

    server.on("/relay/on", []()
    {
        handleRelayOn();
    });

    server.on("/relay/off", []()
    {
        handleRelayOff();
    });

    server.on("/relay/mode", []()
    {
        handleRelayMode();
    });

    server.on("/relay/invert", []()
    {
        handleRelayInvert();
    });

    server.on("/saveLight", []()
    {
        handleSaveLight();
    });

    server.on("/saveFog", []()
    {
        handleSaveFog();
    });

    server.on("/saveFan", []()
    {
    handleSaveFan();
    });

    server.on("/saveAux", []()
    {
    handleSaveAux();
    });

    server.begin();
}

void handleWebServer()
{
    server.handleClient();
}