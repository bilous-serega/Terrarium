#include "globals.h"
#include "web_common.h"

String buildHardwarePage()
{
    String html;

    html += buildPageStart("Hardware");

    html += "<h1>Hardware Settings</h1>";

    html += buildNavigation();

    for (int i = 0; i < 4; i++)
    {
        html += "<hr>";

        html += "<b>";
        html += relays[i].name;
        html += "</b><br><br>";

        html += "Invert Relay: ";

        html += "<a href='/relay/invert?id=";
        html += i;
        html += "&value=";
        html += relays[i].invert ? "0" : "1";
        html += "'>";

        html += relays[i].invert ? "ON" : "OFF";

        html += "</a><br>";
    }

    html += buildPageEnd();

    return html;
}