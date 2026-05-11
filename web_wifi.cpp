#include "wifi_manager.h"
#include "web_common.h"

String buildWiFiPage()
{
    String html;

    html += buildPageStart("WiFi");

    html += "<h1>WiFi Settings</h1>";

    html += buildNavigation();

    html += "Status: ";

    html += isWiFiConnected()
        ? "CONNECTED"
        : "AP MODE";

    html += "<br><br>";

    html += "IP: ";
    html += getWiFiIP();

    html += "<br>";

    html += buildPageEnd();

    return html;
}