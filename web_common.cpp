#include <Arduino.h>
#include <WiFi.h>
#include "globals.h"
#include "rtc_manager.h"

String buildNavigation()
{
    String html;

    html += "<div class='topbar'>";

    html += "<span>";
    html += "TIME: ";
    html += getTimeString();
    html += "</span>";

    html += "<span>";
    html += "DATE: ";
    html += getDateString();
    html += "</span>";

    html += "<span>";
    html += "TEMP: ";
    html += String(climate.temperature, 1);
    html += "C";
    html += "</span>";

    html += "<span>";
    html += "HUM: ";
    html += String(climate.humidity, 0);
    html += "%";
    html += "</span>";

    html += "<span>";
    html += "SENSOR: ";
    html += climate.error;
    html += "</span>";

    unsigned long seconds = millis() / 1000;

    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;

    html += "<span>";
    html += "UP: ";
    html += String(hours);
    html += "h ";
    html += String(minutes);
    html += "m";
    html += "</span>";

    html += "<span>";
    html += "WIFI: ";

        if (WiFi.status() == WL_CONNECTED)
        {
            html += "ONLINE";
        }
        else
        {
            html += "OFFLINE";
        }

    html += "</span>";

    html += "<span>";
    html += "HEAP: ";
    html += String(ESP.getFreeHeap() / 1024);
    html += "KB";
    html += "</span>";

    html += "</div>";

    html += "<div style='margin-bottom:16px;'>";

    html += "<a class='nav-btn' href='/'>";
    html += "Dashboard";
    html += "</a>";

    html += "<a class='nav-btn' href='/automation'>";
    html += "Automation";
    html += "</a>";

    html += "<a class='nav-btn' href='/hardware'>";
    html += "Hardware";
    html += "</a>";

    html += "<a class='nav-btn' href='/wifi'>";
    html += "WiFi";
    html += "</a>";

    html += "</div>";

    return html;
}

String buildSystemCard()
{
    String html;

    unsigned long seconds = millis() / 1000;

    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds % 3600) / 60;

    html += "<div class='card'>";

    html += "<h2>System</h2>";

    html += "Uptime: ";
    html += String(hours);
    html += "h ";
    html += String(minutes);
    html += "m";

    html += "<br>";

    html += "Free Heap: ";
    html += String(ESP.getFreeHeap() / 1024);
    html += " KB";

    html += "</div>";

    return html;
}

String buildPageStart(const String& title)
{
    String html;

    html += "<html><head>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<meta charset='utf-8'>";
    html += "<title>";
    html += title;
    html += "</title>";
    html += "<style>";

    html += "body{";
    html += "background:#111827;";
    html += "color:#f3f4f6;";
    html += "font-family:Arial,sans-serif;";
    html += "padding:12px;";
    html += "margin:0;";
    html += "}";

    html += "h1,h2{";
    html += "color:#ffffff;";
    html += "}";

    html += "a{";
    html += "color:#60a5fa;";
    html += "text-decoration:none;";
    html += "margin-right:8px;";
    html += "}";

    html += "hr{";
    html += "border:1px solid #374151;";
    html += "}";

    html += "input{";
    html += "background:#1f2937;";
    html += "color:#f3f4f6;";
    html += "border:1px solid #374151;";
    html += "padding:6px;";
    html += "border-radius:6px;";
    html += "}";

    html += "input[type=submit]{";
    html += "background:#2563eb;";
    html += "border:none;";
    html += "padding:8px 14px;";
    html += "cursor:pointer;";
    html += "}";

    html += ".card{";
    html += "background:#1f2937;";
    html += "padding:12px;";
    html += "border-radius:10px;";
    html += "margin-bottom:14px;";
    html += "box-shadow:0 0 8px rgba(0,0,0,0.3);";
    html += "}";

    html += ".nav-btn{";
    html += "display:inline-block;";
    html += "background:#2563eb;";
    html += "color:white;";
    html += "padding:8px 12px;";
    html += "border-radius:8px;";
    html += "margin:4px;";
    html += "text-decoration:none;";
    html += "}";

    html += ".nav-btn:hover{";
    html += "background:#1d4ed8;";
    html += "}";

    html += ".btn{";
    html += "display:inline-block;";
    html += "padding:6px 10px;";
    html += "border-radius:6px;";
    html += "margin:2px;";
    html += "text-decoration:none;";
    html += "color:white;";
    html += "font-size:14px;";
    html += "}";

    html += ".btn-on{";
    html += "background:#10b981;";
    html += "}";

    html += ".btn-off{";
    html += "background:#ef4444;";
    html += "}";

    html += ".btn-auto{";
    html += "background:#2563eb;";
    html += "}";

    html += ".btn-manual{";
    html += "background:#f59e0b;";
    html += "}";

    html += ".badge{";
    html += "display:inline-block;";
    html += "padding:4px 8px;";
    html += "border-radius:999px;";
    html += "font-size:12px;";
    html += "margin-right:6px;";
    html += "color:white;";
    html += "}";

    html += ".badge-on{";
    html += "background:#10b981;";
    html += "}";

    html += ".badge-off{";
    html += "background:#ef4444;";
    html += "}";

    html += ".badge-auto{";
    html += "background:#2563eb;";
    html += "}";

    html += ".badge-manual{";
    html += "background:#f59e0b;";
    html += "}";

    html += ".badge-source{";
    html += "background:#6b7280;";
    html += "}";

    html += ".topbar{";
    html += "background:#1f2937;";
    html += "padding:10px;";
    html += "border-radius:10px;";
    html += "margin-bottom:16px;";
    html += "font-size:14px;";
    html += "}";

    html += ".topbar span{";
    html += "margin-right:14px;";
    html += "}";

    html += "</style>";
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
