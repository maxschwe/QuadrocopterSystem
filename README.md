Dieses Projekt entstand im Rahmen meiner Seminar- und Bachelorarbeit am **Lehrstuhl für Regelungstechnik der Universität Augsburg**. Es umfasst die Entwicklung eines modularen Quadrocopter-Systems zur Evaluation moderner Regelungsstrategien und soll vor allem in der Lehre eingesetzt werden.

## 🚀 Kern-Features
* **Rapid Prototyping:** Entwicklung von Regelalgorithmen in Simulink und Implementierung mit **Simulink Embedded Coder**.
* **Live-Monitoring:** Separate Bodenstation (Desktopanwendung) zur Echtzeit-Visualisierung von Telemetriedaten und zur Steuerung der Drohne.
* **Systemidentifikation:** Erstellung eines präzisen physikalischen Modells basierend auf Daten von Prüfständen und realen Closed-Loop-Flugdaten.

## 🧩 System
### Systemübersicht
![overview](/docs/images/overview.png)
*Kernkomponenten des Quadrocoptersystems*

### Modellübersicht
![model](/docs/images/model.png)
*Struktur des mathematischen Quadrocopter-Modells.*

### Controllerübersicht
![controller](/docs/images/controller.png)
*Aufbau des Kaskadenreglers*

## 🎮 Regelungsstrategien
Im Fokus stand der Vergleich verschiedener Reglerarchitekturen innerhalb einer **Kaskadenstruktur** (jeweils einen Regler für Position und Lage):
* **Klassisch:** PID-Regler
* **Optimal:** LQ-Regler

## 🛠 Verwendete Technologien
* **Hardware:** ESP32 (Microcontroller), MPU6050 (IMU).
* **Model-Based Design:** MATLAB, Simulink, Embedded Coder.
* **Embedded & Scripting:** ESP-IDF mit C++ (Onboard-Software), Python (Bodenstation, Systemidentifikation), Julia (Systemidentifikation).
