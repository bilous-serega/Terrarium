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
        html += "</b><br><br>";

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

        html += "<br><br>"; //html += "<br>";

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

    html += "<a class='btn btn-on' href='/relay/on?id=";
    html += i;
    html += "'>ON</a> ";

    html += "<a class='btn btn-off' href='/relay/off?id=";
    html += i;
    html += "'>OFF</a> ";

    html += "<a class='btn btn-auto' href='/relay/mode?id=";
    html += i;
    html += "&value=auto'>AUTO</a> ";

    html += "<a class='btn btn-manual' href='/relay/mode?id=";
    html += i;
    html += "&value=manual'>MANUAL</a>";

    html += "<br><br>";

    }

    html += "</div>";

    html += buildPageEnd();

    return html;
}