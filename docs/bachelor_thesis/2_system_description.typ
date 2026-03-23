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
    content((5.1, 3.0), [RC-Empfänger], anchor: "west", fill: col)

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
Die implementierte Softwarearchitektur besteht aus einer Onboard-Software für den Quadrocopter und einer Bodenstationssoftware, welche auf einem normalen PC läuft. Auf diese beiden Komponenten wird nun genauer eingegangen.

=== Bodenstation Software
Die Bodenstation besteht aus einer Desktopanwendung, welche die Steuerung der Drohne sowie die Erfassung, Speicherung und Auswertung von Telemetriedaten erlaubt (vgl. @ground_station). Die Software verfügt über eine modulare Konfiguration zur Echtzeitvisualisierung relevanter Parameter wie Orientierung, Position und Stellgrößen. Zudem können Sprünge, harmonische Schwingungen und einige weitere Trajektorien initiiert und automatisiert aufgezeichnet werden. Diese können anschließend anhand definierter Kenngrößen, wie dem Mean Squared Error (MSE), evaluiert werden. Parallel dazu verarbeitet die Anwendung im Hintergrund die Positionsdaten des Lasertrackers und übermittelt diese über die serielle Kabelverbindung an den Mikrocontroller.

#figure(
  image("resources/groundstation.png", height: 21em),
  caption: [GUI der Bodenstationssoftware],
) <ground_station>

=== Onboard-Software
Für die Implementierung der Onboard-Software wurde das ESP-IDF Framework von Expressif Systems @EspressifEspidf2026 verwendet, welches die grundlegenden Werkzeuge zur Entwicklung von Mikrocontroller Software liefert. Darunter fallen Softwarebibliotheken, z. B. zur Verwendung von Hardwareperipherien, aber auch Tools zur grundsätzlichen Kompilierung, zum Flashen und zum Monitorn des Mikrocontrollers. Da das Framework auf dem Echtzeitbetriebssystem freeRTOS basiert, erlaubt es effizientes Multitasking bei deterministischem Verhalten.

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
          Interruptgesteuert, $200 "Hz"$\
          Priorität: 10
        ]
      ], shape: rect, fill: blue.lighten(60%)),
      
      node((1,0), align(center)[
        *Control Task*\
        #text(size: 0.8em)[
          Periodisch mit $200 "Hz"$\
          Priorität: 5
        ]
      ], shape: rect, fill: lime.lighten(60%)),
      
      node((0,1), align(center)[
        *RC Task*\
        #text(size: 0.8em)[
          UART Ereignisgesteuert, ca. $45 "Hz"$\
          Priorität: 3
        ]
      ], shape: rect, fill: orange.lighten(60%)),
      
      node((1,1), align(center)[
        *Comm Task*\
        #text(size: 0.8em)[
          Periodisch mit $50 "Hz"$\
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

Der IMU-Task ist für die Verarbeitung der Orientierungsdaten zuständig. Mit einer Frequenz von $200 "Hz"$ legt der DMP neue Orientierungsdaten in seinem internen Puffer ab und löst darauf folgend einen Hardware-Interrupt aus, der den IMU-Task aktiviert. Dieser liest die Daten aus der Sensor-Warteschlange aus, transformiert diese in Roll-, Nick- sowie Gierwinkel und stellt diese den Control- und Comm-Tasks zur Verfügung. Aufgrund des begrenzten Puffers des DMP ist der Task mit der höchsten Priorität $10$ versehen, um ein Überlaufen der Warteschlange und damit fehlerhafte Daten zu vermeiden.

Wenn die Fernsteuerung aktiv ist, wertet der RC-Task ca. alle $22 "ms"$ die Fernsteuerungsdaten aus und stellt diese an den Control-Task bereit. Dieser Task ist ereignisgesteuert und läuft, sobald neue RC-Daten auf dem UART Anschluss erhalten werden.

Der Control-Task arbeitet periodisch mit $200 "Hz"$ und ist für die geregelte Ansteuerung der Aktoren zuständig. Die Führungsgrößen werden bei der Verwendung der Fernsteuerung vom RC-Task bezogen, andernfalls von der Bodenstation über den Comm-Task. Die Lagedaten liefert der IMU-Task, die Positionsdaten des Lasertrackers der Comm-Task. Als Sicherheitsfunktion werden die Rotoren automatisch abgeschaltet, sollte der Control-Task für mehr als 500 ms keine aktuellen Mess- oder Führungsgrößen empfangen.

Der Comm-Task sendet alle $20 "ms"$ Telemetriedaten an die Bodenstation und verarbeitet eingehende Befehle. Diese enthalten aktuelle Positionsdaten, neue Führungsgrößen oder Reglerparameter. Mit letzteren lässt sich die Regelung online anpassen, ohne dass die Onboard-Software neu kompiliert und übertragen werden muss, was die Entwicklungszeit erheblich verkürzt.
