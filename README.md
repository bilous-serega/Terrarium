# Terrarium Controller Refactor

## Что изменено

Проект разделён на независимые модули:

- WiFi
- RTC
- Sensors
- Relays
- Automation
- OLED
- Web
- Storage

## Главная цель

Убрать:
- giant ino file
- String fragmentation
- хаотичную архитектуру
- direct hardware access

## Что дальше

Следующий этап:
- перенос всей HTML панели
- перенос всех route handlers
- перенос Preferences
- fail-safe логика
- OTA
- reconnect system
- watchdog
