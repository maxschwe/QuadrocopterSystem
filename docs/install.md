## Install
- VSCode installieren
- ESP-IDF Extension installieren und kurzes, integriertes Setup durchfuehren
- ESP IDF Terminal ueber Terminal Button unten in der Leisten oeffnen
- dont use cmake tools vscode extension; can have problems when saving cmakelists.txt file and you manualy have to delete the build directory

- possibly Ctrl+Shift+p: select CMake Kit: Unspecified
- if error like: fatal error: driver/i2c.h: No such file or directory: #include <driver/i2c.h> => you possibly need to include the component (here driver) into CMAKELists.txt with REQUIRES driver

## Simulink Coder
Model Configuration Parameters -> Math and Data Types -> Default for underspecified data type -> change from 'double' to 'single'

## Build System
[Build System](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html)

## Run
- Flash Methode Uart auswaehlen
- richtigen COM-Port auswaehlen (evtl. muss noch Treiber fuer UART installiert werden, wenn COM-Port nicht gefunden wird)
- Device Target: esp32
- Flamme unten in der Leiste druecken zum Flashen, Builden und Monitoren
