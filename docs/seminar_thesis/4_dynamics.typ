#import("conf/conf-unia-rt.typ"): subfigures

= Dynamische Modellbildung <dynamic_modeling>
Die Gesamtdynamik lässt sich in drei Teildynamiken unterteilen.
Die Antriebsdynamik hängt ausschließlich vom verwendeten Antriebssystem ab, also beim Multicopter insbesondere von den eingesetzten Motoren und Propellern.
Das Kontrolleffektivitätsmodell beschreibt, wie die durch die Antriebe erzeugten Schübe und Momente auf die Gesamtdynamik des Quadcopters wirken, und ist deshalb ausschließlich abhängig von der mechanischen Konfiguration der Antriebe. Dieses Modell liefert generalisierte Stellgrößen, die den resultierenden Schub sowie die Momente beschreiben, welche auf den als starren Körper interpretierten Quadcopter wirken.
Das Modell der starren Körperdynamik beschreibt schließlich die daraus resultierenden konkreten Bewegungen des Fluggeräts.

Diese Aufteilung vereinfacht die Modellbildung und ermöglicht es durch ihre Modularität, Änderungen zum Beispiel an der Antriebskonfiguration – etwa durch unterschiedliche Propelleranordnungen oder Motorcharakteristika – einfach zu berücksichtigen, ohne das gesamte Dynamikmodell anpassen zu müssen. @stephanMulticopterFlightControl2025

== Antriebsdynamik
Bei der Modellbildung der Antriebsdynamik werden drei Effekte vernachlässigt:
+ Die dynamischen Effekte, d.h. die zeitlichen Verzögerungen bis zum Erreichen der gestellten Motordrehzahl,
+ der Bodeneffekt, welcher sich durch eine Effizienzsteigerung des Rotors in Bodennähe zeigt, und
+ der Einfluss auf den Schub bei translatorischer oder rotatorischer Flugbewegung, da sich die Anströmung der Rotorblätter verändert.
Dank dieser Vereinfachungen können der Rotorschub $F$ und das Rotormoment $M$ unabhängig vom Zustand des Quadrocopters allein als Funktionen der Rotorgeschwindigkeit $Omega$ modelliert werden:

$ F(Omega) = c_T Omega^2 $
$ M(Omega) = c_M Omega^2 $

Bei $c_M$ und $c_T$ handelt es sich um zu identifizierende Parameter, welche vom Propeller abhängen. @stephanMulticopterFlightControl2025

Die Dynamik des Motors kann im relevanten Arbeitsbereich von 20% - 80% durch eine lineare Funktion
$ Omega(delta) = k_m delta  + t_m $
der Drosselung $delta$ angenähert werden. Die verwendeten Parameter $k_m$ und $t_m$ sind motorabhängig, haben aber keine direkte physikalische Bedeutung. @wangDynamicsModellingLinear2016

=== Identifikation

Statt einer physikalischen Identifikation wurden diese experimentell mittels eines Teststands ermittelt (vgl. @test_buildings). Dieser besteht aus einer Wippe im statischen Gleichgewicht, an deren einem Ende ein Rotor montiert ist. Über eine Waage auf der anderen Seite lässt sich das Gewicht $m$ für verschiedene Drosselungen online auslesen. Aus diesem Gewicht lassen sich anschließend je nach verwendetem Aufbau entweder der Schub (vgl. @thrust_measurement) oder das Drehmoment (vgl. @torque_measurement) bestimmen, da gilt: 
$ F = m g $
$ M = F dot l = m g l $

Im Teststand beträgt die Armlänge $l=0.2m$, was exakt der Armlänge des realen Systems entspricht.

#subfigures(
  figure(image("resources/ident_thrust_coefficient.jpg", height: 6cm), caption: [Schubmessung]),
  <thrust_measurement>,
  figure(image("resources/ident_torque_coefficient.jpg", height: 6cm), caption: [Momentmessung]),
  <torque_measurement>,
  caption: [Teststände zur Antriebsidentifikation],
  gutter: 3em,
  label: <test_buildings>
)

Bei diesem Aufbau können die konkreten Koeffizienten nicht ermittelt werden, da die Motor- und Rotordynamiken nicht getrennt voneinander identifiziert werden. Sehr wohl können damit aber die Funktionen $F(delta)$ und $M(delta)$ bestimmt werden. Dazu werden die Parameter $a, b "und" c$ eingeführt: 
$ F (delta) = c_T (k_m delta + t_m)^2 = c_T k_m^2 (delta + t_m/k_m)^2 =: a(delta - b)^2 $ <thrust>
$ M (delta) = c_M (k_m delta + t_m)^2 = c_M k_m^2 (delta + t_m/k_m)^2 =: c dot a(delta - b)^2 = c dot F(delta) $ <torque>

Konkret wurde also wie folgt substituiert:
$ a := c_T k_m^2, b := - t_m/k_m, c := c_M/c_T $

Mittels nichtlinearer Optimierung auf den Messdaten der Teststände durch das BFGS-Verfahren lassen sich dann die drei eingeführten Parameter identifizieren als $a=0.0013$, $b=8.5908$ und $c=0.0351$. Man beachte hier, dass diese keine direkte physikalische Bedeutung mehr besitzen.

#subfigures(
  figure(image("resources/thrust_fit.png"), caption: [Identifikation $F(delta)$]),
  figure(image("resources/torque_fit.png"), caption: [Identifikation $M (delta)$]),
  caption: [Ergebnisse der Identifikation der Antriebsdynamik]
)


== Steuerwirksamkeitsmodell <control_effectiveness_model>
Sinnvoll ist es, als generalisierte Stellgrößen $bold(u)$ den Gesamtschub $F_"thrust"$, das Rollmoment $M_x$, das Nickmoment $M_y$ sowie das Giermoment $M_z$ einzuführen @stephanMulticopterFlightControl2025. Für ein System in der in (@Model) gezeigten Konfiguration lassen sich diese wie folgt bestimmen:

Der Gesamtschub $F_"thrust"$ setzt sich zusammen aus der Summe aller Schübe, also: $ F_"thrust"=sum_(i=1)^4 F(delta_i) $
Das Rollmoment sowie das Nickmoment wird durch die respektiven gegenüberliegenden Rotorpaare erreicht. Es gilt:
$ M_x = - F(delta_2)l + F(delta_4)l $
$ M_y = F(delta_1)l - F(delta_3)l $
Die vier Antriebsmomente erzeugen das Gesamtgiermoment, was sich ergibt zu 
$ M_z = M(delta_1) - M(delta_2) + M(delta_3) - M(delta_4) $ 
Hier lässt sich die Wichtigkeit erkennen, dass der erzeugte Schub und das Moment eines Motors linear abhängig sind (vgl. @torque). Ansonsten wäre es nicht immer möglich, diese generalisierten Stellgrößen unabhängig voneinander festlegen zu können.

In Matrizenschreibweise mit der Wirksamkeitsmatrix $bold(B_"eff")$ können diese vier Zusammenhänge zusammengefasst werden zu:
$ bold(u)(delta_1, delta_2, delta_3, delta_4) = vec(F_"thrust", M_x, M_y, M_z) = underbrace(mat(align: #right, 1, 1, 1, 1; 0 , -l, 0, l; l, 0, -l, 0; c, -c, c, -c), bold(B_"eff")) vec(F(delta_1), F(delta_2), F(delta_3), F(delta_4)) $

== Bewegungsgleichungen eines ungebundenen Multicopters
Ziel ist es nun, die translatorischen und rotatorischen Bewegungsgleichungen zu bestimmen. Hierzu können zum Beispiel die Newton-Euler- oder Lagrange-Euler-Formulierungen verwendet werden. In @wangDynamicsModellingLinear2016 werden folgende auch für unser Modell zu übernehmende Annahmen für die Modellierung der Körperdynamik getroffen:
- der Quadrocopter ist ein starrer, symmetrischer Körper
- sein Schwerpunkt liegt im Ursprung des körperfesten Koordinatensystems $K_B$
- Luftwiderstand und gyroskopische Effekte sowohl von den Rotoren als auch vom Quadcopter an sich können vernachlässigt werden

Zunächst müssen noch ein paar Größen eingeführt werden:

Die Trägheitsmatrix $M_"RB"$ eines starren Körpers mit der Masse $m$ und dem Trägheitstensor $bold(I)$ ergibt sich zu:

$ bold(M_"RB") = mat(
  m bold(I_(3 times 3)), bold(0_(3 times 3)); 
  bold(0_(3 times 3)), bold(I)
) $ 

$bold(tau)$ gibt die generalisierten Kräfte an. Sie bestehen in unserem Modell aus der Gravitationskraft $G = m g$ und den generalisierten Stellgrößen $bold(u)$. Im körperfesten Koordinatensystem $K_B$ ergibt sich $bold(tau)$ dann zu: 
$ bold(tau) = vec(
  -m g s_theta, 
  m g s_phi c_theta,
  m g c_phi c_theta - F_"thrust",
  M_x,
  M_y,
  M_z
) $

Damit lassen sich dann gleichsam zum Vorgehen in @kugelbergBlackBoxModelingAttitude2016, jedoch wie oben angenommen ohne Beachtung der gyroskopischen Effekte, die Bewegungsgleichungen bestimmen als:

$ bold(M_"RB") bold(dot(upsilon)) = bold(tau) $

$bold(dot(upsilon))$ bezeichnet wie in @upsilon eingeführt die translatorischen und rotatorischen Beschleunigungen des Systems in $K_B$. Mit @relation_eta_upsilon können die Bewegungsgleichungen dann in $K_E$ überführt werden, sodass gilt:
$ bold(dot.double(eta)) = bold(J) dot bold(M_"RB"^(-1)) tau $ <motion_equations_earth>

=== Linearisierung
@motion_equations_earth wird im Hoverzustand mit $psi_0=0$ linearisiert. Im Hoverzustand muss $F_("thrust", 0)=m g$ sowie $phi=theta=0$ gelten. Es gilt dann laut @kugelbergBlackBoxModelingAttitude2016:

$ dot.double(eta) = J_"lin" dot M_"RB"^(-1) tau_"lin" $
mit 
$ tau_"lin" = vec(
  -m g theta,
  m g phi,
  - (F_"thrust" - F_("thrust", 0)),
  M_x,
  M_y,
  M_z
) $

Damit lässt sich schlussendlich dann folgendes Zustandsraummodell wie in @oktayDynamicModelingSimulation2019 aufstellen:

$ 
bold(x) = vec(eta, dot(eta)), Delta bold(u) = bold(u) - bold(u_0)
\
bold(dot(x)) = A bold(x) + B Delta bold(u) \
bold(y) = bold(x) \
A = mat(
  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0;
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0;
  0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0;
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0;
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0;
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1;
  0, 0, 0, 0, -g, 0, 0, 0, 0, 0, 0, 0; 
  0, 0, 0, g, 0, 0, 0, 0, 0, 0, 0, 0; 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 
), 

B = mat(
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  0, 0, 0, 0;
  - 1/m, 0, 0, 0;
  0, 1/I_(x x), 0, 0;
  0, 0, 1/I_(y y), 0;
  0, 0, 0, 1/I_(z z)
) 
$

=== Identifikation 
Für die Bewegungsgleichungen müssen nun noch $m$ und $bold(I)$ identifiziert werden. Das Gewicht lässt sich sehr einfach messen. Der Trägheitstensor $bold(I)$ des starren Körpers hat aufgrund der Annahme als symmetrisch bezüglich $K_B$ die Gestalt einer Diagonalmatrix. Für die Bestimmung des Trägheitsmoments um jede Achse wurde das in @setatiExperimentalApproachCalculate2022 vorgestellte Verfahren verwendet. Hierbei wird die Drohne in verschiedenen Orientierungen an einem Doppelpendel befestigt und dann rotatorisch um die vertikale Achse ausgelenkt (vgl. @ident_traegheitsmoment). Mit der gemessenen Schwingungsperiodendauer und den Maßen des Versuchaufbaus lässt sich dann das Trägheitsmoment um die vertikale Achse bestimmen. 

#subfigures(
  figure(image("resources/Ixx_ident.jpg"), caption: [$I_(x x)$]),
  figure(image("resources/Iyy_ident.jpg"), caption: [$I_(y y)$]),
  figure(image("resources/Izz_ident.jpg"), caption: [$I_(z z)$]),
  columns: (auto, auto, auto),
  caption: [Testaufbauten zur Identifikation der Trägheitsmomente],
  label: <ident_traegheitsmoment>
)

Die fehlenden Parameter wurden bestimmt zu: $m = 1.014 "kg"$, $I_(x x) = 0.0258 "kg" m^2$, \ $I_(y y) = 0.0268 "kg" m^2$, $I_(z z)=0.0680 "kg" m^2$.

== Bewegungsgleichungen auf einem rotatorischen 3-DOF Teststand
Auf einem rotatorischen 3-DOF Teststand fallen die drei translatorischen Freiheitsgrade weg. Wenn der Masseschwerpunkt SP jedoch nicht genau auf dem rotatorischen Fixpunkt liegt, erzeugt die Gewichtskraft nun wie bei einem Pendel ein rotatorisches Moment. Ist der SP unterhalb des Fixpunkts, so hat die Gewichtskraft einen stabilisierenden Effekt, liegt er dagegen darüber, so wird die Instabilität verstärkt. Genau das ist beim verwendeten System der Fall, da sich der SP $d = 0.05 m$ über dem Fixpunkt befindet. Das erzeugte Drehmoment ergibt sich zu:
$ bold(M_G) = bold(r_"SP") times bold(G) $
Konkret in $K_B$ also als:
$ bold(M_G) = vec(0, 0, -d) times (bold(R^(-1)) vec(0, 0, m g)) = vec(m g s_phi c_theta d, m g s_theta d, 0) $

Damit ergeben sich die Bewegungsgleichungen für die rotatorischen Freiheitsgrade als:

$ bold(dot.double(Phi)) = bold(T) bold(I^(-1)) vec(M_x + m g s_phi c_theta d, M_y + m g s_theta d, M_z) $

Das lineare Zustandsraummodell stellt sich auf als:

