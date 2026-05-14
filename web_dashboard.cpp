#include "globals.h"
#include "rtc_manager.h"
#include "web_common.h"
#include "automation.h"

String buildDashboardPage()
{
    String html;

    html += buildPageStart("Dashboard");

    html += "<h1>Terrarium Controller</h1>";

    html += buildNavigation();

    if (warningState != WARNING_NONE)
{
    html += "<h2>WARNING</h2>";

    switch (warningState)
    {
        case WARNING_SENSOR_TIMEOUT:
            html += "SENSOR TIMEOUT";
            break;

        case WARNING_RTC_ERROR:
            html += "RTC ERROR";
            break;

        default:
            html += "UNKNOWN WARNING";
            break;
    }

    html += "<br><br>";
}

    html += "<div class='card'>";
    
    html += "<h2>Relays</h2>";

    for (int i = 0; i < 4; i++)
    {
        html += "<hr>";

        html += "<b>";
        html += relays[i].name;
        html += "</b><br>";

        html += "<span class='badge ";

        html += relays[i].state ?
            "badge-on" :
            "badge-off";

        html += "'>";

        html += relayStateText(relays[i].state);

        html += "</span>";

        html += "<span class='badge ";

        html += relays[i].autoMode ?
            "badge-auto" :
            "badge-manual";

        html += "'>";

        html += relayModeText(relays[i].autoMode);

        html += "</span>";

        html += "<span class='badge badge-source'>";

    switch (relays[i].source)
{
        case SOURCE_MANUAL:
            html += "MANUAL";
            break;

        case SOURCE_AUTOMATION:
            html += "AUTOMATION";
            break;

        case SOURCE_SYSTEM:
            html += "SYSTEM";
            break;

        case SOURCE_FAILSAFE:
            html += "FAILSAFE";
            break;
}

        html += "</span>";

html += "<br>";

html += "<span class='badge badge-source'>";

if (i == 0)
{
    html += isFogHumidityRequested() ?
        "AUTOMATION ACTIVE" :
        "AUTOMATION IDLE";
}
else if (i == 1)
{
    html += isFanTemperatureRequested() ?
        "AUTOMATION ACTIVE" :
        "AUTOMATION IDLE";
}
else
{
    switch (relays[i].source)
    {
        case SOURCE_MANUAL:
            html += "MANUAL CONTROL";
            break;

        case SOURCE_AUTOMATION:
            html += "AUTOMATION CONTROL";
            break;

        case SOURCE_SYSTEM:
            html += "SYSTEM CONTROL";
            break;

        case SOURCE_FAILSAFE:
            html += "FAILSAFE CONTROL";
            break;
    }
}

    html += "</span>";

    html += "<br><br>";
    }

    html += "</div>";

    html += buildPageEnd();

    return html;
}