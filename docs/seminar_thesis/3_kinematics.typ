#import("resources/models.typ") as models
#import("conf/conf-unia-rt.typ"): subfigures

= Kinematische Modellbildung <Model>
Zur kinematischen Beschreibung dienen die klassischen Methoden der Starrkörpermechanik @sicilianoKinematics2025. 
Man führt ein körperfestes, kartesisches Koordinatensystem $K_B$ ein, dessen Ursprung im Masseschwerpunkt gewählt wird. Für dessen konkrete Orientierung gibt es bei Quadcoptern keine einheitlichen Konventionen. Bei der Plus-Konfiguration wird die x-Achse genau auf einer Rotorachse gewählt und vereinfacht so das in @control_effectiveness_model beschriebene Steuerwirksamkeitsmodell. Zusätzlich ist die Plus-Konfiguration im Vorwärtsflug aerodynamisch effizienter, da die Luftströmung effektiver nach unten abgeleitet und keine Verwirbelung im Zentrum erzeugt wird @ComputationalStudyRotor. Dagegen findet die X-Konfiguration vor allem bei Kameradrohnen Anwendung, da hier die in Vorwärtsrichtung zeigende x-Achse zwischen zwei Rotorachsen liegt und somit keine Achse die Kamera stört. @quanIntroductionMulticopterDesign2017 
Auch keine einheitlichen Konventionen gibt es für die Nummerierung der Rotoren und ob die z-Achse nach oben oder unten zeigt. Im Folgenden soll die Plus-Konfiguration (vgl. @plus_config) mit der eingezeichneten Nummerierung verwendet werden.

#subfigures(
  figure([#models.drone_model(true)], caption: [Plus-Konfiguration]),
  <plus_config>,
  figure([#models.drone_model(false)], caption: [X-Konfiguration]),
  caption: [Quadrocopterkonfigurationen]
)

Zusätzlich muss noch ein meist erdfestes Referenzkoordinatensystem $K_E$ eingeführt werden. Hierzu eignet sich zum Beispiel ein lokales, kartesisches System, was in der folgenden dynamischen Modellbildung auch verwendet wird. Die Position wird dann mit den Koordinaten des Ursprungs von $K_E$ im Referenzsystem angegeben als der Vektor $bold(p)$. Eine Alternative bietet auch das geografische Gradnetz der Erde, bei dem die Position in Längen- und Breitengrad sowie einer Höhe angegeben wird. 

Zur Beschreibung der Orientierung eines starren Körpers in Relation zu einem Bezugsytem existieren drei gängige Methoden. Die Angabe dreier Eulerwinkel, welche die Orientierung als drei aufeinanderfolgende Rotationen um verschiedene Koordinatenachse beschreiben ist dabei die intuitivste. Im Luft- und Raumfahrtkontext wird üblicherweise die Roll-Nick-Gier-Konvention ($phi, theta, psi$) verwendet. Allerdings weist die Beschreibung mittels Eulerwinkeln Singularitäten auf, das heißt, bestimmte Orientierungen können durch unterschiedliche Winkelkombinationen äquivalent beschrieben werden. Dies erschwert insbesondere die Entwicklung von Regelungsalgorithmen, da kleine Änderungen der Orientierung große Variationen in den Eulerwinkeln verursachen können.
Die Rotationsmatrix $bold(R) in "SO"(3)$ ist dagegen frei von Singularitäten und eignet sich direkt zur im folgenden Abschnitt gezeigten Koordinatenraumtransformation. Sie enthält jedoch redundante Informationen, da neun Einträge zur Beschreibung von lediglich drei Freiheitsgraden erforderlich sind. Aus diesem Grund stellt die Verwendung von Einheitsquaternionen eine kompakte und eindeutige Alternative zur Beschreibung der Orientierung dar. @sicilianoKinematics2025

Im Folgenden soll die Position $bold(p)$ und Orientierung $bold(Phi) = [ phi, theta, psi ]^T$ im Inertialsystem $K_E$ als $bold(eta)$ mit 
$ bold(eta) = mat(x, y, z, phi, theta, psi)^T $
zusammengefasst werden.
Die lineare und rotatorische Geschwindigkeit im körperfesten Koordinatensystem $K_B$ wird dagegen durch den Vektor $bold(upsilon)$ festgelegt:
$ bold(upsilon) = mat(u, v, w, p, q, r)^T $ <upsilon>

== Koordinatenraumtransformation
Im Folgenden sollen diese Kurzschreibweisen verwendet werden: 
$ s_alpha:= sin(alpha), c_alpha := cos(alpha), t_alpha := tan(alpha) $
Für die Transformation von Vektoren vom Koordinatenraum $K_B$ in den Koordinatenraum $K_E$ kann die Rotationsmatrix $bold(R)$ eingeführt werden @stephanMulticopterControlFundamentals2025: 
$ bold(R) = attach(bold(R), tl: E, b: B) = mat(
  c_theta c_psi, s_phi s_theta c_psi - c_phi s_psi, c_phi s_theta c_psi+s_phi s_psi; 
  c_phi s_psi , s_phi s_theta s_psi + c_phi c_psi, c_phi s_theta s_psi - s_phi c_psi;
  -s_theta, s_phi c_theta, c_phi c_theta
) $ <rotation_matrix>

Eine Rotationsmatrix ist orthonormal, weshalb die transponierte Matrix gleich der Inversen ist:
$ attach(bold(R), tl: B, b: E) = bold(R)^(-1) = bold(R)^T $

Vektoren können zwischen den Koordinatensystemen dann transformiert werden mit:
$ attach(bold(v), tl: E) = attach(bold(R), tl: E, b: B) dot attach(bold(v), tl: B) $

Die Transformationsmatrix $bold(T)_omega$ aus @stephanMulticopterControlFundamentals2025 wandelt Roll-Pitch-Yaw-Ableitungen in $K_B$ zu Winkelgeschwindigkeiten in $K_E$ um:

$ bold(T)_omega = mat(
  1, s_phi t_theta, c_phi t_theta;
  0, c_phi, -s_phi;
  0, s_phi/c_theta, c_phi/c_theta
) $ <generalized_transformation_matrix>

Beide Matrizen können wie in @kugelbergBlackBoxModelingAttitude2016 in einer generalisierten Transformationsmatrix $bold(J)$ zusammengefasst werden als:
$ bold(J) = mat(bold(R), bold(0)_(3 times 3); bold(0)_(3 times 3), bold(T)_omega) $

Mit dieser können dann die eingeführten Größen $bold(eta)$ und $bold(upsilon)$ in Relation miteinander gesetzt werden durch:
$ dot(bold(eta)) = bold(J) dot bold(upsilon) $ <relation_eta_upsilon>

Ein Quadcopter hat seine Arbeitspunkte, wenn er sich im Hoverzustand befindet, also $phi = theta = 0$ und $psi = psi_0$. Die linearisierten Matrizen ergeben sich somit als:
$ bold(R)_"lin" (psi_0) = mat(c_psi_0, -s_psi_0,  0; s_psi_0, c_psi_0, 0; 0, 0, 1) $
und
$ bold(T)_omega_"lin" = bold(I)_(3 times 3) $
