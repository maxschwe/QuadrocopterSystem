#import "conf/conf-unia-rt.typ": subfigures
#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge

= Systemaufbau

Das untersuchte System (vgl. @whole_system) besteht aus vier BLDC-Motoren, die jeweils in einem Winkel von $90 degree$ zueinander angeordnet sind. Nebeneinanderliegende Rotoren drehen jeweils in unterschiedliche Richtungen, um die erzeugten Drehmomente auszugleichen. Die Ansteuerung der Motoren erfolgt über den Diatone Mamba F55_128K ESC. Er verwendet das BLHeli_32 ESC-Firmware System, welches verschiedene digitale und analoge Kommunikationsprotokolle zum Setzen der vier Drehzahlen erlaubt. Das einfachste davon ist die Übermittlung eines PWM-Signals mit Frequenzen von 50 - 500Hz. Nach einer kurzen Initialisierungssequenz werden Pulsweiten von 1 - 2ms  linear auf eine Drosselstellung von 0 - 100% abgebildet. Die Erfassung der Orientierungsdaten erfolgt über einen MPU6050-Sensor. Mithilfe der Bibliothek aus @I2cdevlibESP32_ESPIDFComponents kann der integrierte Digital Motion Processor (DMP) des Sensors mit einer maximalen Frequenz von 200Hz angesprochen werden, der die Rohdaten bereits onboard filtert und anschließend über den I²C-Bus an den Controller überträgt (vgl. @sensor_system). Als Hauptcontroller kommt ein ESP32 zum Einsatz, der aufgrund seines günstigen Preises, seiner hohen Rechenleistung sowie der Vielzahl an integrierten Schnittstellen und Funktionen für diese Anwendung besonders geeignet ist. Zudem erlaubt das zugehörige ESP-IDF Framework es recht einfach, ein auf freeRTOS basierendes Echtzeitsystem für die Softwareentwicklung zu verwenden @EspressifEspidf2025.

#subfigures(
  figure(image("resources/structure.jpg"), caption: [
    Gesamtsystem
  ]), <whole_system>,
  figure(diagram(
    node-stroke: 1pt,
    node-corner-radius: 2pt,
    spacing: 1.5em,
    node((0, 0), [
      #place(dy: -1.5em)[
          MPU6050
      ]
      #diagram(
        node-stroke: 1pt,
        node-corner-radius: 2pt, {
          node((0, 0), [Accelerometer], name: <acc>)
          node((0, 1), [Gyroskop], name: <gyro>)
          node((1, 0.5), [DMP], name: <dmp>)
          let verts = ( // () means the previous vertex
           ((), "-|", (<gyro.east>, 50%, <dmp.west>)),
           ((), "|-", <dmp>), <dmp>
          )
          edge(<acc>, ..verts, "-|>")
          edge(<gyro>, ..verts)
        }
      )
    ]),
    edge("<|-|>", [$I^2C$]),
    node((0, 2), [ESP32], name: <esp32>),
    
  ), caption: [Sensorsytem]), <sensor_system>,
  columns: (1fr, 1fr),
  caption: [Systemaufbau],
  label: <full>,
)
