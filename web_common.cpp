#include <Arduino.h>

String buildNavigation()
{
    String html;

    html += "<hr>";
    html += "<a href='/'>Dashboard</a> | ";
    html += "<a href='/automation'>Automation</a> | ";
    html += "<a href='/hardware'>Hardware</a> | ";
    html += "<a href='/wifi'>WiFi</a>";
    html += "<hr>";

    return html;
}

String buildPageStart(const String& title)
{
    String html;

    html += "<html><head>";
    html += "<meta charset='utf-8'>";
    html += "<title>";
    html += title;
    html += "</title>";
    html += "</head><body>";

    return html;
}

String buildPageEnd()
{
    return "</body></html>";
}

String relayModeText(bool mode)
{
    return mode ? "AUTO" : "MANUAL";
}

String relayStateText(bool state)
{
    return state ? "ON" : "OFF";
}
