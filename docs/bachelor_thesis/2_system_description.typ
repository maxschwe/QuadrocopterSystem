#import "conf/conf-unia-rt.typ": subfigures
#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import "@preview/cetz:0.4.2"

= Systembeschreibung

Das Gesamtsystem gliedert sich in vier Subsysteme (vgl. @overview):

1. Lasertracker: Erfasst die Position des Quadrocopters und übermittelt die Positionsdaten via Ethernet an die Bodenstation.

2. Bodenstation: Verarbeitet die Trackerdaten und sendet diese zusammen mit Steuerbefehlen an den Quadrocopter. Zudem wertet diese empfangene Telemetriedaten aus. Die Kommunikation mit dem Quadrocopter erfolgt kabelgebunden über eine serielle Schnittstelle.

3. Quadrocopter: Das Herzstück des Systems, welches regelungstechnisch untersucht wird.

4. Fernsteuerung (optional): Ermöglicht eine manuelle Steuerung über einen separaten Funklink.

#figure(
  diagram(
    node-stroke: 1pt,
    node-corner-radius: 5pt,
    spacing: 4.5em,
    node((0, 0), [#image("resources/gyrotheodolite-surveying-icon.svg", height: 5em) Lasertracker], shape: rect),
    edge("-|>", [Ethernet]),
    // Added 'shape: rect' to force rectangular borders
    node((1, 0), [#image("resources/pc-icon.svg", height: 5em) Bodenstation], shape: rect),
    edge("<|-|>", [UART]),
    node((2, 0), [
      #image("resources/drone-icon.svg", height: 4em)
      Quadrocopter
    ], shape: rect),

    node((1, 0.8), [#image("resources/gamepad-icon.svg", height: 5em) Fernsteuerung], shape: rect, stroke: (dash: "dashed")),
    edge((1, 1), (2, 0), "-|>", [Funklink], label-side: right),
  ), 
  caption: [Systemüberblick (Fernsteuerung ist optional)]
) <overview>

// https://uxwing.com/drone-icon/
// https://uxwing.com/pc-icon/

Im Rahmen dieser Arbeit wurde die Avionik und Onboard-Software des Quadrocopters sowie die Software der Bodenstation entwickelt. Auf diese Komponenten soll im Folgenden genauer eingegangen werden.

== Hardwareaufbau des Quadrocopters
Der Quadrocopteraufbau basiert mechanisch auf dem Quadrocopter Control System (QCS) von Emqopter @QuadrotorControlSystem, welches ebenfalls für die Lehre entwickelt wurde. Da aber wesentliche Teile ihrer Software proprietär sind, ist eine vollständige Integration eigener Regelungsalgorithmen nur schwer möglich. Daher wurde zwar der mechanische Aufbau inklusive des 3-DOF-Teststands übernommen (vgl. @mechanical_system) und die meisten elektronischen Komponenten wiederverwendet, der Flugcomputer jedoch basierend auf einem ESP-WROOM-32 grundlegend neu entwickelt.

#figure(
  cetz.canvas({
    import cetz.draw: *

    let col = rgb("#ff8c00")

    // for centering image
    rect((-7.85, -5.8), (7.85, 5.8), stroke: 0pt)
    
    content((0,0), image("resources/3dof_teststand.jpg", height: 27.5em))
    
    line((0, 5), (5, 5.5), stroke: 1pt + col)
    content((5.1, 5.5), [Retroreflektor], anchor: "west", fill: col)

    line((0.5, -3.7), (5, -4.0), stroke: 1pt + col)
    content((5.1, -4.0), [Netzteil], anchor: "west", fill: col)

    line((1.0, 3.6), (5, 3.0), stroke: 1pt + col)
    content((5.1, 3.0), [RC Empfänger], anchor: "west", fill: col)

    line((0.0, -1.5), (-5, -2.7), stroke: 1pt + col)
    content((-5.1, -2.7), [Stativ], anchor: "east", fill: col)

    line((-2, 3.1), (-5, 2.5), stroke: 1pt + col)
    content((-5.1, 2.5), [Motor], anchor: "east", fill: col)

    line((-0.3, 4.1), (-5, 4.3), stroke: 1pt + col)
    content((-5.1, 4.3), [ESP32], anchor: "east", fill: col)
  }),
  caption: [Quadrocopter auf dem 3-DOF-Teststand]
) <mechanical_system>

Die Avionik (@avionics) umfasst neben dem Mikrocontroller folgende Komponenten:
1. MPU6050-Sensor: Dieser dient der Erfassung der Lagedaten. Dabei wird der integrierte Digital Motion Processor (DMP) genutzt, welcher die Rohdaten des Beschleunigungssensors und Gyroskops direkt onboard fusioniert. Er liefert über die $"I"^2"C"$-Schnittstelle gefilterte Euler-Winkel zur Lagebeschreibung.
2. RC-Empfänger: Er empfängt die Steuerbefehle der Fernsteuerung und übermittelt diese via UART an den ESP32.
3. Diatone Mamba F55_128K ESC @MAMBAF55_128KBL32: Ermöglicht die Ansteuerung der vier Rotoren über verschiedene Protokolle. Im vorliegenden System erfolgt die Vorgabe der Rotordrehzahl über ein PWM-Signal (490 Hz). Dabei werden Pulsweiten von $1 - 2$ ms linear auf eine Drosselstellung von $0\%$ bis $100\%$ abgebildet. Zusätzlich ist an diesen noch eine externe Stromquelle angeschlossen, welche den Strom für die Rotoren liefert und über die zukünftig auch der Mikrocontroller angeschlossen werden kann.
4. BLDC-Motoren: Vier bürstenlose Gleichstrommotoren wandeln die ESC-Signale in Schubkraft um.

#figure(image("resources/wiring.png"), caption: [Avionik des Quadrocoptersystems]) <avionics>

== Softwarearchitektur

=== Bodenstation Software
Die Bodenstation ermöglicht die Steuerung der Drohne sowie die Erfassung, Speicherung und Auswertung von Telemetriedaten. Hierfür wurde eine Desktop-Anwendung in Python unter Verwendung des GUI-Toolkits Tkinter entwickelt (vgl. @ground_station). Die Software bietet eine modulare Konfiguration zur Echtzeitvisualisierung ausgewählter Telemetrieparameter (z. B. Orientierung, Position, Stellgrößen, ...). Darüber hinaus lassen sich verschiedene Trajektorien initiieren, z. B. Sprünge oder harmonische Schwingungen und automatisiert aufzeichnen, um sie im Anschluss anhand definierter Bewertungsgrößen wie z. B. einem Mean Squared Error zu analysieren. Zudem verarbeitet diese im Hintergrund die Positionsdaten des Lasertrackers und sendet diese über die serielle Kabelverbindung an den Mikrocontroller.

#figure(
  rect(width: 100%, height: 280pt, stroke: 2pt + gray, fill: luma(240))[
    Kommt noch, wenn sie wirklich in der finalen Version ist
  ],
  caption: [GUI der Bodenstationssoftware],
) <ground_station>

=== Onboard-Software
Für die Implementierung der Onboard-Software wurde das ESP-IDF Framework von Expressif Systems @EspressifEspidf2026 verwendet, welches die grundlegenden Werkzeuge zur Entwicklung von Mikrocontroller Software liefern. Darunter fallen Softwarebibliotheken z. B. zur Verwendung von Hardwareperipherien aber auch Tools zur grundsätzlichen Kompilierung, zum Flashen und zum Monitorn des Mikrocontrollers. Da das Framework auf dem Echtzeitbetriebssystem freeRTOS basiert, erlaubt es effizientes Multitasking und trotzdem deterministisches Verhalten.

In der implementierten Onboard-Software wurden vier parallel laufende Tasks verwendet (@task_overview), welche mit unterschiedlichen Taktraten laufen und für verschiedene Aufgaben zuständig sind:

#figure(diagram(
  node-stroke: 1pt,
  node-corner-radius: 5pt,
  spacing: (3em, 4em),
  
  // Haupt-Container
  node((0,0), [
    *FreeRTOS Task Übersicht*
    #v(0.2em)
    
    #diagram(
      spacing: (2em, 2em),
      
      // Tasks
      node((0,0), align(center)[
        *IMU Task*\
        #text(size: 0.8em)[
          Interruptgesteuert, ca. 200Hz\
          Priorität: 10
        ]
      ], shape: rect, fill: blue.lighten(60%)),
      
      node((1,0), align(center)[
        *Control Task*\
        #text(size: 0.8em)[
          Periodisch mit 200Hz\
          Priorität: 5
        ]
      ], shape: rect, fill: lime.lighten(60%)),
      
      node((0,1), align(center)[
        *RC Task*\
        #text(size: 0.8em)[
          UART Ereignisgesteuert, ca. 45Hz\
          Priorität: 3
        ]
      ], shape: rect, fill: orange.lighten(60%)),
      
      node((1,1), align(center)[
        *Comm Task*\
        #text(size: 0.8em)[
          Periodisch mit 50Hz\
          Priorität: 2
        ]
      ], shape: rect, fill: red.lighten(60%)),
      
      // Datenflüsse
      edge((0,0), (1,0), "-|>"),
      edge((0,0), (1,1), "-|>"),
      edge((0,1), (1,0), "-|>"),
      edge((1, 0), (1,1), "<|-|>"),
    )
  ], shape: rect, stroke: 2pt + black),
  
), caption: [FreeRTOS Tasks mit zugehörigen Datenflüssen]) <task_overview>

Der IMU-Task verarbeitet die Orientierungsdaten. Sobald neue Daten in der Warteschlange des MPU6050 verfügbar sind, löst dieser einen Hardware Interrupt aus, welcher den IMU-Task aktiviert. 


Sensor gesendet werden. Er wird durch einen Hardware Interrupt durch den MPU6050 Sensor aktiviert, ließt die Daten aus der DMP-Warteschlange des Sensors aus und speichert die umgewandelten Roll-, Pitch- und Yaw-Werte ab, sodass diese vom Control- und Comm-Task abgefragt werden können. Der Sensor liefert gefilterte Lagedaten mit einer Taktrate von ca. 200Hz. Aufgrund der begrenzten Puffergröße des Sensors ist dieser Task mit der höchsten Priorität versehen, um fehlerhafte Daten zu vermeiden.

Wenn die Fernsteuerung aktiv ist, wertet der RC-Task ca. alle 22ms die Fernsteuerungsdaten aus und stellt diese an den Control-Task bereit. Dieser Task ist ereignisgesteuert und läuft, sobald neue RC-Daten auf dem UART Anschluss erhalten werden.

Der Control-Task arbeitet periodisch mit 200Hz und ist für die geregelte Ansteuerung der Aktoren zuständig. Die Lagedaten erhält er vom IMU-Task, die Positionsdaten vom Comm-Task. Je nach verwendetem Betriebsmodus liefert die Führungsgrößen entweder der RC-Task oder der Comm-Task. Erhält der Control-Task länger als 100ms keine neuen Mess- oder Führungsgrößen, so werden die Rotoren automatisch abgeschalten. Zusätzlich kann der Comm-Task auch konfiguriert werden, dass er verschiedene Parameter für den Regler liefern kann, wodurch sich diese dann online direkt von der Bodenstationssoftware aus konfigurieren lassen, ohne dass der Mikrocontroller-Code neu kompiliert und geflasht werden muss.

Der Comm-Task wertet alle 20ms von der Bodenstation erhaltene Befehle aus, konkret Führungsgrößen und Reglerparameter und sendet anschließend Telemetrie-Daten zurück. Diese enthalten Mess-, Führungs- und Stellgrößen sowie flexible Reglerparameter, welche unter anderem für Debugging-Zwecke genutzt werden können.
