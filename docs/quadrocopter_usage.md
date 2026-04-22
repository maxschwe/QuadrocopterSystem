## Schritte zum Testen des Systems
### Vorgehen zum Flashen eines neuen Reglers
- Regler in Simulink entwickeln (in einem Referenced Model, welches also einen eigenen Solver hat; nur dann funktioniert es gut, nur den Regler in Code umzuwandeln und nicht das ganze Model, vgl. `/docs/simulink_embedded_coder.md`); in diesem Projekt kann `controller_3dof_container.slx` oder `controller_6dof_container.slx` direkt verwendet werden (in diesen Dateien sind schon alle Coder-Einstellungen richtig)
- mit Simulink Embedded Coder Source Code generieren (nicht schon kompilierten Code)
- den Ordner der Onboard Software (`/src`) im Terminal öffnen bzw. direkt nur diesen Ordner in VSCode
- `copy_3dof_controller.bat` bzw. `copy_6dof_controller.bat` ausführen (diese kopieren den generierten Source-Code aus dem `/model` Ordner in den richtigen Ordner des `/src` Ordners)
- mit ESP-IDF Onboard-Code kompilieren, flashen und monitorn (der Flamme-Button unten in der VSCode Leiste bzw. `Ctrl+E` gefolgt von `Ctrl+D` ohne die `Ctrl`-Taste loszulassen)
> [WARNING]
>
> Wenn das System im freien Flug betrieben wird, müssen das Netzteil oder der Schalter an der Drohne deaktiviert sein, bevor die Onboard-Software geflasht wird. Ansonsten hebt das System ab, ohne dass die Bodenstation und damit die Positionsmessung aktiv ist.

- Monitor-Terminal killen z. B. mit Papierkorb Button oben rechts im Terminal (notwendig, da die serielle Verbindung von der Bodenstation benötigt wird und nicht zwei Programme gleichzeitig auf einen seriellen Port zugreifen können)

### Vorgehen zum Starten des Systems auf dem Teststand
- Verwendung der Bodenstation optional (aber sinnvoll, um Trajektorien zu starten und aufzuzeichnen)
- kann auch gestartet werden, wenn die Onboard-Software schon läuft und die Motoren aktiv sind (dann startet aber die Onboard-Software automatisch neu und damit die Motoren, was an dem neuen Öffnen der seriellen Verbindung liegt)

### Vorgehen zum Starten des Systems im freien Flug
> [WARNING]
>
> Sicherstellen, dass Netzteil bzw. Schalter an dem Quadrocopter noch deaktiviert ist, sodass die Motoren nicht laufen (Onboard-Software kann bzw. eher sollte schon laufen)

- Quadrocopter auf den Boden stellen in die Richtung, dass der Pfeil auf dem Quadrocopter in Richtung des Fensters zeigt (sodass Koordinatensystem von Lasertracker und Quadrocopter gleich ausgerichtet ist)
- Spiegel auf die initale Position auf dem Lasertracker auflegen
- Starten der Bodenstationssoftware
    - Öffnen des `/ground_station` Ordners in einem neuen VSCode Fenster
    - wenn Python-Extension aktiv sollte das `uv`-Environment automatisch aktiviert werden, wenn ein Terminal geöffnet wird -> im Terminal `python src/main.py` ausführen
    - ansonsten `uv run python src/main.py`
- Warten bis Desktopanwendung mit den Telemetriedaten angezeigt wird (wenn nicht geöffnet wahrscheinlich Probleme mit Lasertracker)
- Spiegel von Lasertracker auf die Drohne platzieren, aber aufpassen, dass Lasertracker nicht den Spiegel verliert (verliert der Lasertracker einmal den Spiegel, so muss man die Bodenstation komplett neustarten, da dann aus irgendeinem Grund der Lasertracker nicht mehr den Measurement Callback in dem Python Programm auslöst)
- in Telemetriedaten checken, dass korrekte Positionsdaten erhalten werden
- Reset Button auf ESP-32 Controller drücken (Button links vom USB-Port, wenn man von unten auf den Port schaut); mit Finger aufpassen, dass man sie nicht innerhalb den Rotoren hat :)
- schnell das Netzteil bzw. den Button an der Drohne aktivieren, sodass die Motoren aktiv sind (sollte passieren, bevor die PWM-Initialisierungssequenz für den ESC ausgeführt wird (man hat 2s in etwa Zeit))
- Drohne hebt leicht vom Boden ab und braucht kurz bis der I-Anteil den Bodeneffekt ausgleicht und die Drohne wirklich direkt am Boden schwebt (am besten mit den Händen zumindest am Anfang die Drohne an dem Außenschutz leicht festhalten, dass man sie einfangen kann, wenn sie nen Schmarn macht)
- z-Position auf `0.7 m` setzen, um die Drohne in die Luft zu bringen (ist die Startposition für die Trajektorien)

### Vorgehen zum Stoppen des Systems im freien Flug

- Drohne langsam runter bringen, also z= `0.3`, `0.2`, `0.1`, `0.0` da die z-Führung etwas überschwingt und die Drohne sonst auf den Boden kracht, der Lasertracker den Spiegel verliert und die Drohne sich dann unkontrolliert bewegt
- Motoren aus (mit Schalter an Drohne oder an Netzteil)
- Bodenstation stoppen (das wirklich erst als letztes, da beim Schließen der Software die serielle Verbindung geschlossen wird und dann der Quadrocopter automatisch einen Neustart ausführt, heißt die Motoren abschaltet)

## Beachten
- je nach verwendetem Betriebsmodus (Teststand (3-DOF) vs freier Flug (6-DOF)) und Regler (PID vs LQ) müssen bzw. sollten Config Variablen angepasst werden in:
    - `/src/components/Drone/include/drone.h`
    - `/ground_station/main.py`
- Flashen der Onboard-Software muss immer passieren, wenn die Bodenstationssoftware nicht läuft, da die gleiche serielle Verbindung zum Flashen und zum Monitorn verwendet wird

## Bodenstation
- über `ground_station/src/plots.py` kann konfiguriert werden, welche Telemetriedaten angezeigt werden (je nach 3-DOF vs 6-DOF-Modus); die verfügbaren Telemetriedaten können in `ground_station/src/telemetry_data.py` ausgelesen werden
- `value1-6` können für flexible Parameter verwendet werden, um z. B. Regler zu debuggen (im Simulink Modell sind diese eigene Outports, welchen beliebige Parameter zugewiesen werden können); diese können dann auch ganz einfach angezeigt werden in der Bodenstation mit dem zugehörigen Namen
- mit `ground_station/src/plot_recording_file.py` können aufgenomme Telemetriedaten im Nachhinein nochmal in der GUI angezeigt werden

## Fernsteuerung
- in `src/main/main.cpp` kann die Fernsteuerung aktiviert werden
- diese überschreibt dann die Führungsgrößen der Bodenstation und kann zur Steuerung des Systems verwendet werden
- bei Verwendung muss der Flip-Schalter an der linken, oberen Seite der Fernsteuerung verwendet werden, um die Motoren entgültig zu starten bzw. auch wieder abzuschalten
