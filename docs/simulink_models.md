## Übersicht
- `sim_xxx`-Models sind die Hauptdateien, welche zur Simulation des 3-DOF bzw. 6-DOF Verhaltens genutzt werden können
- `xxx_container`-Models sind die Modelle, welche mit automatischer Codegenierung umgewandelt werden (diese enthalten den Regler selbst aber auch eine Simulation des Systems mit dem Modell (diese wird auch auf dem Onboard-Computer ausgeführt); dies erlaubt eine schnelle und flexible Visualisierung des Modelverhaltens zu dem realen System online)
- `controller_xxx`: echte Regleralgorithmen
