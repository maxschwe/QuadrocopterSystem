## Install
- VSCode installieren
- ESP-IDF Extension installieren und kurzes, integriertes Setup durchführen
- ESP IDF Terminal über Terminal Button unten in der Leisten öffnen

- dont use cmake tools vscode extension; can have problems when saving cmakelists.txt file and you manualy have to delete the build directory
- possibly Ctrl+Shift+p: select CMake Kit: Unspecified
- if error like: fatal error: driver/i2c.h: No such file or directory: #include <driver/i2c.h> => you possibly need to include the component (here driver) into CMAKELists.txt with REQUIRES driver

## Build System
[Build System](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html)

## Wichtig
CONFIG_FREERTOS_HZ=1000 in sdkconfig Datei setzen. Kann auch über idf.py menuconfig passieren. Diese Rate gibt an, mit welcher Frequenz vtaskDelay und der Scheduler arbeitet. Standard ist 100Hz, also T=10ms. Dann funktioniert vtaskdelay nicht für < 10ms, da delay/T so immer 0 ergibt wegen Integer Division. Dadurch gibt es immer einen Fehler während Programmausführung, weil unser Programm nicht mehr den Idle Task laufen lässt

## Run
- Flash Methode Uart auswählen
- richtigen COM-Port auswählen (evtl. muss noch Treiber fuer UART installiert werden, wenn COM-Port nicht gefunden wird)
- Device Target: esp32
- Flamme unten in der Leiste drücken zum Flashen, Builden und Monitoren
