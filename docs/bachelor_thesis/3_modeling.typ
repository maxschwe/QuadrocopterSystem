#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import "conf/conf-unia-rt.typ": runin, show_plot
#import "resources/models.typ": drone_model

#import "@preview/mitex:0.2.6": *

= Modellbildung

Das folgende Kapitel beschreibt die mathematische Modellierung des Quadrocopters, welche das Fundament für den Entwurf modellbasierter Regler sowie für die computergestützte Simulation des Systemverhaltens bildet. Diese Modellbildung baut auf der vorausgegangenen Seminararbeit @zotero-item-538 auf und wurde vor allem unter Einbezug der Theorien von @stephanMulticopterFlightControl2025 und @quanIntroductionMulticopterDesign2017 weiterentwickelt. Zunächst werden die kinematischen und dynamischen Zusammenhänge beschrieben. Darauf folgt die Parameteridentifikation, bei der sich vor allem auf die Identifikation mit realen Flugdaten konzentriert wird. Den Abschluss bildet die Linearisierung des Modells, bei der das Modell in eine lineare Zustandsraumdarstellung überführt wird, die für viele modellbasierte Regelungsstrategien Voraussetzung ist.

== Kinematik und Dynamik
Das Modell lässt sich, wie in @model_overview dargestellt, in drei aufeinanderfolgende Teilmodelle unterteilen. Diese Struktur basiert auf der Annahme, dass die Antriebsdynamik nicht vom Zustand des Quadrocopters beeinflusst wird und das rotatorische Verhalten vollständig vom translatorischen Verhalten entkoppelt ist. Dies stellt eine Vereinfachung der Realität dar, da sehr wohl physikalische Kopplungen zwischen diesen Teilen des Systems bestehen. Beispielsweise erhöht sich der Schub in Bodennähe (sog. Bodeneffekt, vgl. @leeAdaptiveAltitudeFlight2023) und während einer schnellen Vorwärtsbewegung des Copters verringert sich die Effizienz der Antriebe. Auf die mathematische Abbildung dieser komplexen Wechselwirkungen wird im vorliegenden Modell jedoch bewusst verzichtet, da deren Einfluss im moderaten, nicht hochdynamischen Flugbetrieb gering ist. @stephanMulticopterFlightControl2025

#figure(
  diagram(
    node-stroke: 0.7pt,
    spacing: 3em,
    label-sep: 0.2em,
    node-corner-radius: 5pt,
    
    // Nodes (Blocks) - Using explicit coordinates
    node((0, 0), [Antriebsmodell], name: <prop>),
    node((0.35, 1), [Rotationsmodell], name: <rot>),
    
    node((-0.35, 2), [Translationsmodell], name: <trans>),
    edge(<trans>, (-0.35, 3), "-|>", label: [$x$, $y$, $z$]),

    edge((0.35, 1.5), (0, 1.5), (0, 2), "-|>", label-side: right),
    
    edge((0, -1), <prop>, "-|>", label: [$bold(delta)$]),
    edge((0.35,0), <rot>, "-|>", label: [$bold(tau)_"ctrl"$], label-side: left),
    edge((-0.35, 0), <trans>, "-|>", label: [$F_"t"$], label-pos: 0.175),
    edge(<rot>, (0.35, 3), "-|>", label: [$phi.alt$, $theta$, $psi$], label-side: left, label-pos: 0.175),
  ),
  caption: [Zusammenspiel der Teilmodelle eines Quadrocopters]
) <model_overview>

Zur mathematischen Beschreibung des Systems werden das Inertialkoordinatenystem $K_"E"$ und das körperfeste Koordinatensystem $K_"B"$ mit Ursprung im Masseschwerpunkt des Quadrocopters eingeführt. Der Flugkörper wird in Plus-Konfiguration angenommen, was bedeutet, dass die Vorwärtsbewegung entlang der $x$-Achse parallel zu einem der Rotorarme verläuft (siehe @coord_system). Das Inertialsystem $K_"E"$ ist zu Beginn des Fluges deckungsgleich mit $K_"B"$ und verbleibt ortsfest an dieser Ausgangsposition.

#figure(drone_model(true), caption: [Koordinatensysteme und Rotorkonfigurationen]) <coord_system>

Im inertialen Raum $K_"E"$ wird der translatorische Zustand des Quadrocopters durch den Positionsvektor $bold(p)=[x, y, z]^top$ und den Geschwindigkeitvektor $bold(v) = [dot(x), dot(y), dot(z)]^top$ definiert. Die Orientierung des Flugkörpers gegenüber $K_"E"$ ergibt sich aus den Euler-Winkeln $bold(eta) = [phi.alt, theta, psi]^top$. Im Gegensatz dazu wird die Winkelgeschwindigkeit um die drei Körperachsen im körperfesten Raum $K_"B"$ durch den Vektor $bold(omega) = [p, q, r]^top$ beschrieben.

Zur Transformation von freien Vektoren mit Koordinaten in $K_"B"$ in freie Vektoren mit Koordinaten in $K_"E"$ kann die Rotationsmatrix $bold(R)$ in Abhängigkeit von der aktuellen Lage $bold(eta)$ des Quadrocopters verwendet werden @krishnaswamiRigidBodyMechanics2025:
$  bold(R)(bold(eta)) = #text(0.79em, $ mat(
  cos(theta) cos(psi), sin(phi.alt) sin(theta) cos(psi) - cos(phi.alt) sin(psi), cos(phi.alt) sin(theta) cos(psi) + sin(phi.alt) sin(psi); 
  cos(theta) sin(psi) , sin(phi.alt) sin(theta) sin(psi) + cos(phi.alt) cos(psi), cos(phi.alt) sin(theta) sin(psi) - sin(phi.alt) cos(psi);
  -sin(theta), sin(phi.alt) cos(theta), cos(phi.alt) cos(theta)
) #h(2.9em) $) $ <rotation_matrix>

// Antriebsmodell
#runin[Antriebsmodell]
Das Antriebsmodell beschreibt den Zusammenhang zwischen den Stellgrößen der Motoren und den resultierenden Kräften und Momenten auf den Quadrocopter. Die hier dargestellte Modellierung basiert auf @zotero-item-538. Unter Vernachlässigung dynamischer Effekte lassen sich die Schubkraft $f_i$ und das Drehmoment $tau_i$ eines einzelnen Rotors in Abhängigkeit der Drosselung $delta_i in [0, 1]$ wie folgt annähern:

$ 
f_i &= a(delta_i - b)^2
$ <thrust>
$
tau_i &= c dot f_i 
$


Die Parameter $a, b$ und $c$ repräsentieren keine direkten physikalischen Konstanten, sondern sind empirische Koeffizienten, die experimentell identifiziert werden müssen. Mithilfe der Steuerungseffektivitätsmatrix $bold(B)_"eff"$ werden die Einzelkräfte der Rotoren in den Vektor der verallgemeinerten Eingangsgrößen $bold(u)$ transformiert. Dieser umfasst den Gesamtschub $F_"thrust"$ sowie die Steuermomente $bold(tau)_"ctrl"$ um die drei körperfesten Achsen:
$ bold(u) = vec(F_"thrust", tau_"ctrl,x", tau_"ctrl,y", tau_"ctrl,z") = underbrace(mat(align: #right, 1, 1, 1, 1; l , 0, -l, 0; 0, l, 0, -l; c, -c, c, -c), bold(B)_"eff") vec(f_1, f_2, f_3, f_4) $ <b_eff>
Diese Matrix ist abhängig von der geometrischen Anordnung der Rotoren und deren Hebelarm $l$ zum Schwerpunkt. Durch die gezielte Steuerung der vier Motordrosselungen können diese vier verallgemeinerten Eingangsgrößen unabhängig voneinander beeinflusst werden, was in @control_alloc bei der Steuerungszuweisung gezeigt wird. Gleichzeitig lässt sich hier aber auch die Unteraktuierung des Systems erkennen, da trotzdem nur vier der sechs Freiheitsgrade unabhängig voneinander kontrolliert werden können. Die getrennte Betrachtung der Antriebsdynamik ist sinnvoll, da dadurch der physikalische Aufbau des Antriebssystems vom restlichen System entkoppelt wird. Wenn sich dann zum Beispiel die Anzahl der Rotoren von vier auf sechs erhöht, muss lediglich die Steuerungseffektivitätsmatrix angepasst werden, während die restlichen Modelle unverändert bleiben können, solange die Änderung der Masse und der Trägheitmomente vernachlässigbar ist. @quanIntroductionMulticopterDesign2017

// Rotationsmodell
#runin[Rotationsmodell]

Für die Modellierung der Rotationsdynamik wird der gesamte Quadrocopter als Starrkörper angenommen. Dann kann die Euler'sche Kreiselgleichung verwendet werden, um das System im körperfesten Koordinatensystem zu beschreiben. Die Wahl dieses Bezugsystems ist sinnvoll, da hier der Trägheitstensor unverändert bleibt. @krishnaswamiRigidBodyMechanics2025
$ bold(J) bold(dot(omega)) + bold(omega) times (bold(J) bold(omega)) = bold(tau) $

Die Umrechnung der Winkelgeschwindigkeiten vom körperfesten Koordinatensystem in die zeitliche Ableitung der Euler-Winkel im Inertialsystem erfolgt über die Transformationsmatrix $bold(T)$:
$ bold(dot(eta)) = bold(T)(bold(eta)) bold(omega) $
mit
$ bold(T)(bold(eta)) := mat(
  1, sin(phi.alt) tan(theta), cos(phi.alt) tan(theta); 
  0, cos(phi.alt), -sin(phi.alt);
  0, sin(phi.alt) \/ cos(theta), cos(phi.alt)\/cos(theta)
) $ 
Diese Transformation unterscheidet sich von einer reinen Orientierungstransformation mit der Rotationsmatrix $bold(R)$, da die einzelnen Euler-Winkelgeschwindigkeiten auf verschiedenen Zwischenkoordinatensystemen basieren @teichmannDynamicsFlightStability1959. 

Im freien Flug wird angenommen, dass nur die Steuermomente $bold(tau)_"ctrl"$ ein äußeres Drehmoment auf den Quadrocopter erzeugen:

$ bold(tau) = bold(tau)_"ctrl" $

Beim Betrieb auf dem 3-DOF-Teststand entsteht aufgrund des vertikalen Versatzes $h$ des Schwerpunkts zum Drehpunkt ein Gravitationsmoment $bold(tau)_g$. Die Drohne verhält sich hier wie ein inverses Pendel in der instabilen (oberen) Ruhelage. Es gilt:

$ bold(tau)_"g" = vec(0, 0, h) times bold(R^(-1))(bold(eta)) vec(0, 0, -m g) = vec(m g sin(phi.alt) cos(theta) h, m g sin(theta) h , 0) $

Zusätzlich soll auch noch ein dämpfendes Moment $bold(tau)_"d"$ aufgrund von Reibung modelliert werden, welches linear bzgl. der Winkelgeschwindigkeit angenommen wird:
$ bold(tau)_"d" = vec(d_x, d_y, d_z) omega^top $

Für das Gesamtmoment auf dem Teststand ergibt sich damit:
$ bold(tau) = bold(tau)_"ctrl" + bold(tau)_"g" + bold(tau)_"d" $

// Translationsmodell
#runin[Translationsmodell]

Das Translationsmodell wird vollständig im Inertialkoordinatensystem entwickelt. Die Bewegungsgleichungen basieren auf dem zweiten Newton'schen Axiom:

$ bold(F) = m bold(dot(v)) $

Dabei wird angenommen, dass die Gesamtkraft $bold(F)$ ausschließlich aus der Gewichtskraft und der Schubkraft besteht. Die Gewichtskraft $bold(F)_"g" = [0, 0, -m g]^top$ wirkt in negativer $z$-Richtung des Inertialsystems. Die Schubkraft $bold(F)_"t" = bold(R) (bold(eta)) [0, 0, F_"t"]^top$ wirkt dagegen in positiver $z$-Richtung des körperfesten Koordinatensystems. Mithilfe der Rotationsmatrix $bold(R)$ (@rotation_matrix) wird diese Kraft in das Inertialsystem transformiert. Die resultierende Gesamtkraft ergibt sich somit zu:
$ bold(F) = bold(F)_"g" + bold(F)_"t" $

#runin[Translations- und Rotationsmodell im Zustandraum]
 Es lassen sich Translations- und Rotationsmodell im Zustandsraum zusammensetzen. Der Zustandsvektor $bold(x)$ umfasst die Position $bold(p)$, die Geschwindigkeit $bold(v)$, die Orientierung $bold(eta)$ und die Winkelgeschwindigkeit $bold(omega)$. Hierbei ist erneut zu beachten, dass die Winkelgeschwindigkeit $bold(omega)$ im körperfesten Koordinatensystem definiert ist. Die anderen Zustandsgrößen werden dagegen im inertialen Raum angegeben:

$ bold(x) = [bold(p), bold(v), bold(eta), bold(omega)]^top $

Die Systemdynamik $bold(dot(x)) = bold(f)(bold(x), bold(u))$ ergibt sich somit zu:
$
vec(bold(dot(p)), bold(dot(v)), bold(dot(eta)), bold(dot(omega))) = 
vec(bold(v), m^(-1)bold(F),bold(T) bold(omega), bold(J)^(-1) (bold(tau) - bold(omega) times (bold(J) bold(omega)) )) 
$

// Im vorgestellten System können nur die Position und Orientierung gemessen werden, nicht jedoch die Geschwindigkeit und Winkelgeschwindigkeit. Dadurch ergibt sich die Ausgangsgleichung zu:
// $
// bold(y) = [bold(p), bold(eta)]^top
// $

== Parameteridentifikation

Wie in @zotero-item-538 dargelegt, lassen sich nahezu alle Systemparameter durch gezielte Versuchsaufbauten unabhängig vom Flugbetrieb bestimmen. Die auf diese Weise identifizierten Parameter sind in @open-loop-identified zusammengefasst. Mit diesen ist bereits eine hinreichend genaue Simulation möglich, um erste stabilisierende Regler für das reale System zu entwerfen. Trotzdem lässt sich der Sim-to-Real-Gap durch Erweiterung des Modells und der Verbesserung bereits identifizierter Parameter weiter schließen. Da die Identifikation mit spezifischen Testständen zeit- und hardwareintensiv ist, wurde  ein Verfahren zur Identifikation im geschlossenen Regelkreis implementiert. Dieses erlaubt es, Parameter direkt aus Daten des regulären Flugbetriebs zu extrahieren, was den Identifikationsprozess maßgeblich beschleunigt. 

#figure(table(
columns: (auto, auto),
inset: 5pt,
align: center + horizon,
fill: (x, y) => if y == 0 { gray.lighten(80%) },
[Parameter], [Wert],
[$a$], [$13.06 "N"$],
[$b$], [$0.0859$],
[$c$], [$0.0351 "m"$],
[$l$], [$0.2 "m"$],
[$m$], [$1.210 "kg"$],
[$h$], [$0.05 "m"$],
[$bold(J)$], [#pad(8pt)[$mat(0.0258, 0, 0; 0, 0.0268, 0; 0, 0, 0.0680) "kg" "m"^2$]],
), caption: [Auf Testständen identifizierte Systemparameter]) <open-loop-identified>

Der Identifikationsprozess gliedert sich hierbei in folgende Schritte:
1. Abflug einer Trajektorie am realen Flugsystem auf dem Teststand und dabei Aufzeichnung der Führungsgrößen $bold(w)_"recorded"$ und Ausgangsgrößen $bold(y)_"recorded"$.
2. Definition der Optimierungsfunktion $f_"loss" (bold(w)_"recorded", bold(y)_"recorded")$ (@optim_function). Diese gibt die Abweichung zwischen Realität und Simulation mithilfe eines Mean Squared Error (MSE) an. Intern enthält diese die Simulation für die aufgenommenen Führungsgrößen $bold(w)_"recorded"$.
3. Durchführung einer gradientenbasierten Optimierung mittels BFGS-Verfahren. Mithilfe von automatischer Differentiation kann der Gradient effizient über die gesamte Simulationsstrecke hinweg bestimmt werden. 

#figure(
  diagram(
    node-stroke: 0.7pt,
    spacing: 2.2em,
    label-sep: 0.2em,
    node-corner-radius: 5pt,

    node([$bold(w)_"recorded"$], stroke: 0pt),
    edge("-|>"),
    node((1, 0), [reales, geregeltes System], stroke: (dash: "dashed")),
    edge((0.3, 0), (0.3, 1), (1, 1), "-|>"),
    node((1, 1), [simuliertes, geregeltes System]),
    edge((1, 0), (2, 0), (2, 0.5), "-|>", label: $bold(y)_"recorded"$, label-side: left, label-pos: 0.36),
    edge((1, 1), (2, 1), (2, 0.5), "-|>", label: $bold(y)_"sim"$, label-side: left, label-pos: 0.2),
    node((2, 0.5), [MSE]),
    edge("-|>"),
    node((3, 0.5), [$f_"cost"$], stroke: 0pt)
  ),
  caption: [Aufbau der Kostenfunktion $f_"cost"$]
) <optim_function>

Bei der Identifikation im geschlossenen Regelkreis ergeben sich im Vergleich zum offenen Regelkreis zwei zentrale Herausforderungen @vandenhofClosedloopIssuesSystem1998:
1. Störungen auf die Ausgangsgröße korrelieren direkt mit den Eingangsgrößen des Systems. Dadurch kann das simulierte Systemverhalten trotz guter Parameter auf Dauer stark von dem realen Verhalten abweichen.
2. Ein Regler ist meist darauf ausgelegt, einen Großteil der Eigendynamik zu unterdrücken. Dadurch kann es schwerer sein, die Parameter der echten Streckendynamik aus den aufgenommen Daten zu extrahieren.

Deshalb ist eine ausreichende Anregung der Systemdynamik entscheidend, damit sich diese auch in den aufgenommen Daten widerspiegelt und mögliche Störungen überdeckt. Aus diesem Grund wurde der Regler absichtlich mit verschiedenen, nicht optimalen Parametern betrieben und es wurden unterschiedliche Trajektorien abgeflogen, um eine möglichst breite Anregung des gesamten Dynamikbereichs zu gewährleisten.

Mithilfe dieses Verfahrens wurden die Dämpfungskonstanten $d_x$, $d_y$ und $d_z$ bestimmt. Ebenso ließen sich der Abstand zwischen Fixpunkt und Schwerpunkt $h$ sowie der Trägheitstensor $bold(J)$ präziser ermitteln, da deren bisherige Bestimmung nur eine begrenzte Genauigkeit zuließ. Die bereits vorhandenen Werte dienten dabei als Startwerte für den Optimierungsalgorithmus. Um die Plausibilität der Ergebnisse zu gewährleisten, wurde der zulässige Suchraum auf eine Abweichung von maximal $20 %$ begrenzt. Da die identifizierten Parameter diese Grenzen nicht erreichten, ist von einer stabilen Lösung auszugehen. Die Ergebnisse sind in der nachstehenden Tabelle aufgeführt:

#figure(table(
columns: (auto, auto),
inset: 5pt,
align: center + horizon,
fill: (x, y) => if y == 0 { gray.lighten(80%) },
[Parameter], [Wert],
[$d_x$], [$0.051 "Nm" "s" "rad"^(-1)$],
[$d_y$], [$0.040 "Nm" "s" "rad"^(-1)$],
[$d_z$], [$0.142 "Nm" "s" "rad"^(-1)$],
[h], [$0.0421 "m"$],
[$bold(J)$], [#pad(8pt)[$mat(0.0276, 0, 0; 0, 0.0295, 0; 0, 0, 0.0551) "kg" "m"^2$]],
), caption: [Auf Testständen identifizierte Systemparameter]) <closed-loop-identified>

Der RMSE aller Achsen konnte im Validierungsdatensatz von $2,38 degree$ auf $1,27 degree$ gesenkt werden. @yaw_closed_loop_identified zeigt beispielhaft, wie sich konkret die Simulation des Yaw-Verhaltens verbessert hat.

#figure(
  show_plot(
    (
      ("plots/yaw_closed_loop_identified.csv", (
        ("Reales gemessenes Verhalten", 1),
        ("Simulation (nicht optimiert)", 2),
        ("Simulation (optimiert)", 3)
      )),
    ),
    [Gier-Winkel $psi$ ($degree$)], 
    raw_data: false
  ),
  caption: [Simulation des Gier-Verhaltens vor und nach der Optimierung]
) <yaw_closed_loop_identified>

== Linearisiertes Modell <lin_model>

Ein lineares Zustandsraummodell ist die Grundvoraussetzung für viele modellbasierte Regelungsverfahren. In dieser Arbeit bildet es die Basis für den Entwurf der beiden LQ-Regler. Es kann jedoch gleichermaßen für komplexere Ansätze wie die modellprädiktive Regelung genutzt werden. Um für die Zukunft eine maximale Flexibilität für den Einsatz des Modells zu gewährleisten, soll das zuvor hergeleitete nichtlineare Zustandsraummodell parametrisch für beliebige Arbeitspunkte linearisiert werden. Anschließend wird es um die Ruhelage der Hover-Position linearisiert. Das Antriebssystem wurde als statisches System modelliert, wodurch dieses nicht Teil des Zustandsraumes ist und deshalb nicht linearisiert werden muss.

#runin[Rotationsdynamik]
Die Linearisierung der Rotationsdynamik $bold(dot(x))_"r" = bold(f)_"r" (bold(x)_"r", bold(tau)_"ctrl")$ erfolgt um einen frei wählbaren Arbeitspunkt $bold(x_("r", 0))=[bold(eta_0), bold(omega_0)]^top$ und das zugehörige Eingangsmoment  $bold(tau_("ctrl", 0))$. Es stellt sich wie folgt auf:
$ 
Delta bold(x)_"r" = bold(x)_"r" - bold(x)_("r", 0)
\
Delta bold(tau)_"ctrl" = bold(tau)_"ctrl" - bold(tau)_("ctrl", 0)
\
Delta bold(dot(x))_"r" = bold(f)_"r" (bold(x)_("r", 0), bold(tau)_("ctrl", 0)) + bold(A)_"r" Delta bold(x)_"r" + bold(B)_"r" Delta bold(tau)_("ctrl") 
\
bold(y)_"r" = bold(C)_"r"bold(x)_("r", 0) + bold(C)_"r" Delta bold(x)_"r"
$ <lin_rot_dynamic>

Für die Systemmatrix $A_"r"$ ergeben sich zwei Varianten, abhängig davon, ob der Quadrocopter im Freiflug oder auf dem Teststand betrieben wird:

$ 
bold(A)_("r", "frei") (bold(x_(r, 0))) = #text(0.60em, mitex(`
\left[\begin{matrix}\left(\omega_{y} \cos{\left(\phi \right)} - \omega_{z} \sin{\left(\phi \right)}\right) \tan{\left(\theta \right)} & \frac{\omega_{y} \sin{\left(\phi \right)} + \omega_{z} \cos{\left(\phi \right)}}{\cos^{2}{\left(\theta \right)}} & 0 & 1 & \sin{\left(\phi \right)} \tan{\left(\theta \right)} & \cos{\left(\phi \right)} \tan{\left(\theta \right)}\\- \omega_{y} \sin{\left(\phi \right)} - \omega_{z} \cos{\left(\phi \right)} & 0 & 0 & 0 & \cos{\left(\phi \right)} & - \sin{\left(\phi \right)}\\\frac{\omega_{y} \cos{\left(\phi \right)} - \omega_{z} \sin{\left(\phi \right)}}{\cos{\left(\theta \right)}} & \frac{\left(\omega_{y} \sin{\left(\phi \right)} + \omega_{z} \cos{\left(\phi \right)}\right) \sin{\left(\theta \right)}}{\cos^{2}{\left(\theta \right)}} & 0 & 0 & \frac{\sin{\left(\phi \right)}}{\cos{\left(\theta \right)}} & \frac{\cos{\left(\phi \right)}}{\cos{\left(\theta \right)}}\\0 & 0 & 0 & 0 & \frac{\omega_{z} \left(J_{yy} - J_{zz}\right)}{J_{xx}} & \frac{\omega_{y} \left(J_{yy} - J_{zz}\right)}{J_{xx}}\\0 & 0 & 0 & \frac{\omega_{z} \left(- J_{xx} + J_{zz}\right)}{J_{yy}} & 0 & \frac{\omega_{x} \left(- J_{xx} + J_{zz}\right)}{J_{yy}}\\0 & 0 & 0 & \frac{\omega_{y} \left(J_{xx} - J_{yy}\right)}{J_{zz}} & \frac{\omega_{x} \left(J_{xx} - J_{yy}\right)}{J_{zz}} & 0\end{matrix}\right]
`))
#h(3.2em)
$
$
bold(A)_("r", "test")(bold(x_(r, 0))) = #text(0.60em, mitex(`
\left[\begin{matrix}\left(\omega_{y} \cos{\left(\phi \right)} - \omega_{z} \sin{\left(\phi \right)}\right) \tan{\left(\theta \right)} & \frac{\omega_{y} \sin{\left(\phi \right)} + \omega_{z} \cos{\left(\phi \right)}}{\cos^{2}{\left(\theta \right)}} & 0 & 1 & \sin{\left(\phi \right)} \tan{\left(\theta \right)} & \cos{\left(\phi \right)} \tan{\left(\theta \right)}\\- \omega_{y} \sin{\left(\phi \right)} - \omega_{z} \cos{\left(\phi \right)} & 0 & 0 & 0 & \cos{\left(\phi \right)} & - \sin{\left(\phi \right)}\\\frac{\omega_{y} \cos{\left(\phi \right)} - \omega_{z} \sin{\left(\phi \right)}}{\cos{\left(\theta \right)}} & \frac{\left(\omega_{y} \sin{\left(\phi \right)} + \omega_{z} \cos{\left(\phi \right)}\right) \sin{\left(\theta \right)}}{\cos^{2}{\left(\theta \right)}} & 0 & 0 & \frac{\sin{\left(\phi \right)}}{\cos{\left(\theta \right)}} & \frac{\cos{\left(\phi \right)}}{\cos{\left(\theta \right)}}\\\frac{m g h \cos{\left(\phi \right)} \cos{\left(\theta \right)}}{J_{xx}} & - \frac{m g h \sin{\left(\phi \right)} \sin{\left(\theta \right)}}{J_{xx}} & 0 & - \frac{d_{x}}{J_{xx}} & \frac{\omega_{z} \left(J_{yy} - J_{zz}\right)}{J_{xx}} & \frac{\omega_{y} \left(J_{yy} - J_{zz}\right)}{J_{xx}}\\0 & \frac{m g h \cos{\left(\theta \right)}}{J_{yy}} & 0 & \frac{\omega_{z} \left(- J_{xx} + J_{zz}\right)}{J_{yy}} & - \frac{d_{y}}{J_{yy}} & \frac{\omega_{x} \left(- J_{xx} + J_{zz}\right)}{J_{yy}}\\0 & 0 & 0 & \frac{\omega_{y} \left(J_{xx} - J_{yy}\right)}{J_{zz}} & \frac{\omega_{x} \left(J_{xx} - J_{yy}\right)}{J_{zz}} & - \frac{d_{z}}{J_{zz}}\end{matrix}\right]
`)) 
#h(3.2em)
$

Im Gegensatz zur Systemmatrix sind die Matrizen $bold(B)_"r"$ und $bold(C)_"r"$ unabhängig vom gewählten Arbeitspunkt, da die zugrunde liegenden Gleichungen bereits einen linearen Zusammenhang aufweisen:

$
bold(B_"r") = #text(1em, mitex(`\left[\begin{matrix}0 & 0 & 0\\0 & 0 & 0\\0 & 0 & 0\\\frac{1}{J_{xx}} & 0 & 0\\0 & \frac{1}{J_{yy}} & 0\\0 & 0 & \frac{1}{J_{zz}}\end{matrix}\right]`))
, " "
bold(C_"r") = #text(1em, $ mat(1, 0, 0, 0, 0, 0;0, 1, 0, 0, 0, 0; 0, 0, 1, 0, 0, 0) $)
$

In der Praxis erfolgt die Regelung meist um eine stationäre Ruhelage. Bei einem Quadrocopter befindet sich diese bei $bold(x)_"r, AP" = [0, 0, phi_0, 0, 0, 0]^top$. Im Folgenden soll zusätzlich $psi_0 = 0$ angenommen werden. Für diesen speziellen Arbeitspunkt ergeben sich die beiden Varianten für die Systemmatrix zu:

$ bold(A)_(r, "frei") (bold(x)_"AP") = mat(0, 0, 0, 1, 0, 0; 0, 0, 0, 0, 1, 0; 0, 0, 0, 0, 0, 1; 0, 0, 0, 0, 0, 0; 0 , 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0) $

$ bold(A)_(r, "test") (bold(x)_"AP") = mat(0, 0, 0, 1, 0, 0; 0, 0, 0, 0, 1, 0; 0, 0, 0, 0, 0, 1; (m g h) / J_"xx", 0, 0, -p_x/J_"xx", 0, 0; 0 , (m g h) / J_"yy", 0, 0, -p_y / J_"yy", 0; 0, 0, 0, 0, 0, -p_z / J_"zz") $

#runin[Translationsdynamik]

Analog zur Rotation wird die Translationsdynamik $bold(dot(x))_"t" = bold(f)_"t" (bold(x)_"t")$ um den Zustand $bold(x)_("t", 0) =[bold(p)_0, bold(v)_0]^top$ und den Eingang $bold(u)_("t", 0) = [F_("thrust", 0), phi.alt_0, theta_0, psi_0]$ linearisiert.
$ 
Delta bold(x)_"t" = bold(x)_"t" - bold(x)_("t", 0)
\
Delta bold(u)_"t" = bold(u)_"t" - bold(u)_("t", 0)
\
Delta bold(dot(x)_"t") = bold(f_"t") (bold(x)_("t", 0), bold(u)_("t", 0)) + bold(A)_"t" Delta bold(x)_"t" + bold(B)_"t" Delta bold(u)_"t" 
\
bold(y) = bold(C)_"t" bold(x)_("t", 0) + bold(C)_"t" Delta bold(x)_"t"
$

Hierbei weist lediglich die Eingangsmatrix $bold(B)_"t"$ eine Abhängigkeit vom gewählten Arbeitspunkt auf, während die Systemmatrix $bold(A)_"t"$ und die Ausgangsmatrix $bold(C)_"t"$ konstant bleiben.

$ bold(A)_"t" = mat(
  0, 0, 0, 1, 0, 0;
  0, 0, 0, 0, 1, 0;
  0, 0, 0, 0, 0, 1;
  0, 0, 0, 0, 0, 0;
  0, 0, 0, 0, 0, 0;
  0, 0, 0, 0, 0, 0
), " " bold(C)_"t" = mat(
  1, 0, 0, 0, 0, 0;
  0, 1, 0, 0, 0, 0;
  0, 0, 1, 0, 0, 0;
) $

$ bold(B_"t") (bold(u)_"t, 0") = #text(0.60em, mitex(`\left[\begin{matrix}0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\\frac{\sin{\left(\phi \right)} \sin{\left(\psi \right)} + \sin{\left(\theta \right)} \cos{\left(\phi \right)} \cos{\left(\psi \right)}}{m} & \frac{F_{t} \left(- \sin{\left(\phi \right)} \sin{\left(\theta \right)} \cos{\left(\psi \right)} + \sin{\left(\psi \right)} \cos{\left(\phi \right)}\right)}{m} & \frac{F_{t} \cos{\left(\phi \right)} \cos{\left(\psi \right)} \cos{\left(\theta \right)}}{m} & \frac{F_{t} \left(\sin{\left(\phi \right)} \cos{\left(\psi \right)} - \sin{\left(\psi \right)} \sin{\left(\theta \right)} \cos{\left(\phi \right)}\right)}{m}\\\frac{- \sin{\left(\phi \right)} \cos{\left(\psi \right)} + \sin{\left(\psi \right)} \sin{\left(\theta \right)} \cos{\left(\phi \right)}}{m} & - \frac{F_{t} \left(\sin{\left(\phi \right)} \sin{\left(\psi \right)} \sin{\left(\theta \right)} + \cos{\left(\phi \right)} \cos{\left(\psi \right)}\right)}{m} & \frac{F_{t} \sin{\left(\psi \right)} \cos{\left(\phi \right)} \cos{\left(\theta \right)}}{m} & \frac{F_{t} \left(\sin{\left(\phi \right)} \sin{\left(\psi \right)} + \sin{\left(\theta \right)} \cos{\left(\phi \right)} \cos{\left(\psi \right)}\right)}{m}\\\frac{\cos{\left(\phi \right)} \cos{\left(\theta \right)}}{m} & - \frac{F_{t} \sin{\left(\phi \right)} \cos{\left(\theta \right)}}{m} & - \frac{F_{t} \sin{\left(\theta \right)} \cos{\left(\phi \right)}}{m} & 0\end{matrix}\right]`)) 
#h(2.5em)
$

Für den speziellen Fall der Hover-Position, in der die Auftriebskraft die Gewichtskraft exakt kompensiert und alle Neigungswinkel Null sind, ergibt sich für die Eingangsmatrix:
$ 
bold(B)_"t" (bold(u)_"AP") = mat(
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, g, 0;
  0, -g, 0, 0;
  1/m, 0, 0, 0
)
$
