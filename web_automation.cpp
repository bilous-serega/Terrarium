#include "web_automation.h"

#include "globals.h"

#include "config_manager.h"
#include "storage_manager.h"

#include "web_common.h"

String buildAutomationPage()
{
    String html;

    html += buildPageStart("Automation");

    html += "<h1>Automation</h1>";

    html += buildNavigation();

    // LIGHT

    html += "<h2>LIGHT</h2>";

    html += "<form action='/saveLight'>";

    html += "ON Hour:<br>";

    html += "<input type='number' ";
    html += "name='on' ";
    html += "min='0' ";
    html += "max='23' ";
    html += "value='";

    html += String(lightConfig.onHour);

    html += "'><br><br>";

    html += "OFF Hour:<br>";

    html += "<input type='number' ";
    html += "name='off' ";
    html += "min='0' ";
    html += "max='23' ";
    html += "value='";

    html += String(lightConfig.offHour);

    html += "'><br><br>";

    html += "<input type='submit' value='SAVE'>";

    html += "</form><br>";

    // FOG

    html += "<h2>FOG</h2>";

    html += "<form action='/saveFog'>";

    html += "START Hour:<br>";

    html += "<input type='number' ";
    html += "name='start' ";
    html += "min='0' ";
    html += "max='23' ";
    html += "value='";

    html += String(fogConfig.startHour);

    html += "'><br><br>";

    html += "STOP Hour:<br>";

    html += "<input type='number' ";
    html += "name='stop' ";
    html += "min='0' ";
    html += "max='23' ";
    html += "value='";

    html += String(fogConfig.stopHour);

    html += "'><br><br>";

    html += "Interval Hours:<br>";

    html += "<input type='number' ";
    html += "name='interval' ";
    html += "min='1' ";
    html += "max='24' ";
    html += "value='";

    html += String(fogConfig.intervalHours);

    html += "'><br><br>";

    html += "Duration Seconds:<br>";

    html += "<input type='number' ";
    html += "name='duration' ";
    html += "min='1' ";
    html += "max='600' ";
    html += "value='";

    html += String(fogConfig.durationSeconds);

    html += "'><br><br>";

    html += "<input type='submit' value='SAVE'>";

    html += "</form><br>";

    // FAN

    html += "<h2>FAN</h2>";

    html += "Temperature automation planned<br><br>";

    // AUX

    html += "<h2>AUX</h2>";

    html += String(auxConfig.onHour);
    html += ":00 -> ON<br>";

    html += String(auxConfig.offHour);
    html += ":00 -> OFF<br><br>";

    html += buildPageEnd();

    return html;
}