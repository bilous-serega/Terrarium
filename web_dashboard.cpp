#include "globals.h"
#include "rtc_manager.h"
#include "web_common.h"

String buildDashboardPage()
{
    String html;

    html += buildPageStart("Dashboard");

    unsigned long seconds = millis() / 1000;

    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;
    unsigned long secs = seconds % 60;

    html += "<h2>System</h2>";

    html += "Uptime: ";
    html += String(hours);
    html += "h ";

    html += String(minutes);
    html += "m ";

    html += String(secs);
    html += "s<br>";

    html += "Free Heap: ";
    html += String(ESP.getFreeHeap() / 1024);
    html += " KB<br><br>";

    html += "<h1>Terrarium Controller</h1>";

    html += buildNavigation();

    html += "<h2>RTC</h2>";

    html += "Status: ";
    html += isRTCValid() ? "OK" : "ERROR";

    html += "<br>";

    html += "Date: ";
    html += getDateString();

    html += "<br>";

    html += "Time: ";
    html += getTimeString();

    html += "<br><br>";

    html += "<h2>Relays</h2>";

    for (int i = 0; i < 4; i++)
    {
        html += "<hr>";

        html += "<b>";
        html += relays[i].name;
        html += "</b><br>";

        html += "State: ";
        html += relayStateText(relays[i].state);

        html += "<br>";

        html += "Mode: ";
        html += relayModeText(relays[i].autoMode);

        html += "<br>Source: ";

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

        html += "<br><br>";

        html += "<a href='/relay/on?id=";
        html += i;
        html += "'>ON</a> ";

        html += "<a href='/relay/off?id=";
        html += i;
        html += "'>OFF</a> ";

        html += "<a href='/relay/mode?id=";
        html += i;
        html += "&value=auto'>AUTO</a> ";

        html += "<a href='/relay/mode?id=";
        html += i;
        html += "&value=manual'>MANUAL</a>";

        html += "<br><br>";
    }

    html += buildPageEnd();

    return html;
}