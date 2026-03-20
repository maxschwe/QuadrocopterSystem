#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import "@preview/cetz:0.4.2": canvas
#import "@preview/cetz-plot:0.1.3": plot

#import "conf/conf-unia-rt.typ": runin, show_plot, subfigures



= Reglerentwurf

Quadrocopter sind inhärent instabile Systeme, da keine natürlichen Rückstellkräfte existieren, die äußeren Störungen entgegenwirken. Beispielsweise führt ein störendes Drehmoment um die Roll-Achse zu einer bleibenden Änderung der Winkelgeschwindigkeit, welche ohne aktiven Eingriff nur sehr langsam durch aerodynamischen Widerstand abgebaut würde. Während sich die Winkelgeschwindigkeit im freien Flug somit näherungsweise grenzstabil verhält, ist der Rollwinkel durch die Integration der Winkelgeschwindigkeit bereits instabil. @stephanMulticopterFlightControl2025 Auf dem verwendeten Teststand verschärft sich dieses Verhalten noch weiter, da hier sogar schon die Winkelgeschwindigkeit aufgrund des versetzten Schwerpunktes instabil ist. Analog dazu zeigt auch das translatorische Verhalten Instabilitäten.

Dieses Systemverhalten macht eine aktive Regelung unumgänglich. Sie dient aber nicht nur der reinen Stabilisierung sondern sorgt auch dafür, dass das System Trajektorien möglichst dynamisch folgen kann. 

Die implementierte Regelungsstruktur besteht aus drei Komponenten: die Positionsregelung, die Lageregelung und die Steuerungszuweisung (siehe @control_overview). Wie auch schon in der Modellbildung wurde die Regelung des Systems in rotatorisches und translatorisches Verhalten unterteilt. Diese Trennung ist in der Praxis aus folgenden Gründen als Standard etabliert @quanIntroductionMulticopterDesign2017:

1. Verringerung der Komplexität: Die Struktur erlaubt es, den Lageregler noch unabhängig von der Positionsregelung zu entwickeln. Sobald dieser dann die gewünschte Dynamik vorweist, kann darauf aufbauend der Positionsregler entwickelt werden.
2. Möglichkeit der Kaskadenreglung: Das rotatorische Verhalten ist deutlich dynamischer als das translatorische. Zusätzlich können Lagedaten mit höherer Frequenz gemessen werden als die Positionsdaten. Daher ist es sinnvoll, die Lageregelung getrennt in einer inneren Schleife mit höherer Taktfrequenz auszuführen.
3. Erhöhte Flexibilität: Bei FPV-Drohnen ist beispielsweise im Flugcomputer nur eine Lageregelung implementiert. Die Positionsregelung übernimmt der Pilot. Dies ist mit dieser Aufteilung relativ leicht umsetzbar. 

#figure(
  diagram(
    node-stroke: 0.7pt,
    // spacing: 3em,
    label-sep: 0.2em,
    node-corner-radius: 5pt,
    
    // Nodes (Blocks) - Using explicit coordinates
    edge((0, -1), <pos>, "-|>", label: $x_"ref", y_"ref", z_"ref"$),
    node((0, 0), [Positionsregelung], name: <pos>),
    node((0.5, 1), [Lageregelung], name: <att>),
    node((0.25, 2), [Steuerungszuweisung / Mixing], name: <mixer>),
    edge((-0.2, 0), (-0.2, 2), "-|>", label: $F_"thrust"$, label-pos: 0.2),
    edge((0.65, -1), (0.65, 1), "-|>", label: $psi_"ref"$, label-pos: 0.2),
    edge((0.35, 0), (0.35, 1), "-|>", label: $phi.alt_"ref", theta_"ref"$),
    edge(<att>, (0.5, 2), "-|>", label: $bold(tau)_"ctrl"$),

    edge(<mixer>, (0.25, 3), "-|>", label: $bold(delta)$)
  ),
  caption: [Reglerübersicht]
) <control_overview>

Als Führungsgrößen für den freien Flug dienen die Position $[x_"ref", y_"ref", z_"ref"]^top$ sowie der Gierwinkel $psi_"ref"$ verwendet. Der Regler berechnet daraus den Stellgrößenvektor $bold(delta) = [delta_1, delta_2, delta_3, delta_4]^top$, welcher die Ansteuerung der vier Motoren definiert.

Im Folgenden werden die drei Kernkomponenten der Regelungsstruktur detailliert erläutert. Für die Positions- sowie die Lageregelung werden jeweils zwei unterschiedliche Reglerentwürfe vorgestellt und vergleichend evaluiert. Abschließend wird die Vorgehensweise zur Implementierung der Algorithmen auf dem Zielsystem dargelegt.

#pagebreak()

== Steuerungszuweisung <control_alloc>

Die Aufgabe der Steuerungszuweisung besteht darin, die von den Reglern geforderten Kräfte und Momente in die Stellbefehle für die einzelnen Motoren umzuwandeln. Im Kontext von Multicoptern wird dies auch häufig als Mixing bezeichnet.

Da sowohl die Steuerungseffektivitätsmatrix $bold(B)_"eff"$ (vgl. @b_eff) als auch der Antriebszusammenhang (vgl. @thrust) invertierbar sind, lassen sich die Stellgrößen direkt berechnen. Es gilt:

$ vec(f_"1, ref", f_"2, ref", f_"3, ref", f_"4, ref") = bold(B)_"eff"^(-1) vec(F_"thrust", tau_x, tau_y, tau_z) $
$ delta_"i, ref" = sqrt(f_"i, ref" / a) + b $

Komplexität entsteht erst, sobald die Stellgrößenbegrenzung berücksichtigt werden muss. Der Arbeitsbereich eines Motors liegt bei einer Drosselung zwischen 15 % und 90 %. Eine einfache Limitierung der einzelnen Motordrehzahlen ist jedoch problematisch: Tritt ein Motor in die Sättigung, ändert sich nicht nur die Amplitude der Schubkraft, sondern insbesondere die Richtung des Momentvektors. Dies führt zu Kopplungen in andere Freiheitsgrade, die vom Regler nicht vorgesehen waren und damit die Stabilität gefährden können. 

Um dieses Problem zu lösen, müssen bereits die verallgemeinerten Stellgrößen $bold(u)$ begrenzt werden. Dies ist mathematisch anspruchsvoll, da die Begrenzung nicht für jede Komponente isoliert, sondern in Abhängigkeit der Gesamtsumme und unter Beibehaltung der Richtung des Drehmomentvektors erfolgen muss. Zusätzlich wird meist der Lagestabilität eine höhere Bedeutung im Vergleich zum Erhalt der Höhe beigemessen, was ebenfalls bei der Steuerungszuweisung beachtet werden muss. @quanIntroductionMulticopterDesign2017

Wird der Quadrocopter jedoch mit einer Schubkraft von ca. 50 % und mit nicht sehr hoher Dynamik betrieben, so werden die Sättungsbereiche selten erreicht. Da dies bei dem untersuchten System als Vorraussetzung fesgesetzt werden kann, wird in dieser Arbeit die Motorstellgrößen trotz der genannten Problematik direkt limitiert. Sollten dadurch kurzzeitige Sättigungseffekte auftreten, so sind die Regler meist robust genug, um die dadurch entstehenden Störmomente relativ schnell auszugleichen. 

== Lageregelung

Wie bereits zu Beginn des Kapitels erläutert wurde, ist das Rotationsverhalten inhärent instabil und muss stabilisiert werden. Da das System nahe der Ruhelage betrieben werden soll, liefert das in @lin_model entwickelte linearisierte Rotationsmodell hier eine gute Approximation. Aus diesem geht hervor, dass die einzelnen Achsen in der Nähe der Ruhelage als entkoppelt betrachtet werden können. Deshalb ist es möglich, die Regler für die einzelnen Achsen getrennt voneinander zu entwickeln.

Das Übertragungsverhalten einer einzelnen Achse entspricht einem System 2. Ordnung, bei dem die Stellgröße direkt auf die Beschleunigung des Orientierungswinkels wirkt. Um einen geeigneten Regler zu entwerfen, wird das linearisierte Verhalten am Beispiel der Roll-Achse auf dem Teststand genauer betrachtet. Für dieses gilt:

$ dot.double(phi.alt) = 1 / J_"xx" (-p_x dot(phi.alt) + m g h phi.alt + tau_x) $

Unter Verwendung des allgemeinen Regelgesetzes $ tau_x = - k_p phi.alt - k_d dot(phi.alt) $ lässt sich das System als homogene Differentialgleichung zweiter Ordnung darstellen und kann in die folgende Form überführt werden:
$ dot.double(y) = - a_1 dot(y) - a_0 y $

Solche idealen Systeme sind asymptotisch stabil, wenn $a_0, a_1 > 0$ @quanIntroductionMulticopterDesign2017. Diese Bedingung ließe sich bereits durch einen reinen P-Regler erfüllen. In diesem Fall wäre die Dämpfung jedoch allein durch aerodynamische Effekte gegeben und somit sehr gering, was zu einer hohen Schwingung des Systems führen wird. Zusätzlich vernachlässigt das idealisierte Modell zusätzliche verzögernde Faktoren, die das reale System trotzdem destabilisieren würden, wie z. B. Aktorverzögerungen, Abtastzeiten des diskreten Reglers und Totzeiten in der Sensordatenverabeitung.

Durch die Hinzunahme eines D-Anteils kann die Phasenreserve erhöht und die Systemantwort gedämpft werden, wodurch auch das reale System zuverlässig stabilisiert wird.

Das System besitzt im Betrieb auf dem Teststand kein integrierendes Verhalten, da $a_0 != 0$ aufgrund des versetzten Schwerpunkts gilt. Deshalb benötigt dieses zwingend einen I-Anteil, um stationäre Genauigkeit zu erreichen. In freifliegender Konfiguration könnte hingegen theoretisch auf den I-Anteil verzichtet werden, da hier $a_0 = 0$ gilt und das System damit bereits ein integrierendes Verhalten aufweist. Jedoch ist auch hier ein I-Anteil meist sinnvoll, um die stationäre Genauigkeit zu verbessern. Bei der Verwendung eines I-Anteils muss beachtet werden, dass dieser eine zusätzliche Verzögerung in das System einführt, was die Phasenreserve verringert und damit die Stabilität gefährden kann. Deshalb muss die Verstärkung des I-Anteils sorgfältig gewählt werden, um einen guten Kompromiss zwischen Regelgüte und Stabilität zu erreichen. @lunzeRegelungstechnik1Systemtheoretische2020

// Die Lagedaten können vom DMP mit lediglich 200 Hz abgefragt werden. Aus diesem Grund ist eine Regelrate von ebenfalls 200 Hz sinnvoll.
// Dies führt zusätzliche Verzögerung in das System ein und begrenzt die Dynamik, wenn gleichzeitig Stabilität gewährleistet werden soll. In der Praxis der Regelungstechnik gilt als bewährte Faustregel, dass die Regelfrequenz etwa 10- bis 20-mal höher sein sollte als die gewünschte Bandbreite des geschlossenen Regelkreises. Dadurch kann der Regler also Schwingungen oder Störungen gut ausgleichen, die langsamer als 10 - 20 Hz sind, bzw. auch Trajektorien gut folgen, die diese Frequenzen aufweisen. 

=== PID

Die einfachste Methode, um einen Regler mit solchen Eigenschaften umzusetzen ist der PID-Regler (@att_pid). Dieser wendet die proportionalen, integralen und derivativen Anteile direkt auf die Regelabweichung $e = phi_"ref" - phi_"meas"$ an, wodurch automatisch eine Folgeregelung realisiert wird. @lunzeRegelungstechnik1Systemtheoretische2020 Um die Verstärkung von hochfrequenten Messrauschen zu begrenzen, wird ein realer D-Anteil mit einem Tiefpassfilter $G(s) = N / (s+N)$ verwendet. Dieser verhindert extrem hohe Amplituden in der Stellgröße, welche das System destabilisieren können.

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    edge-corner-radius: none,
    spacing: 3em,

    node((0.2, 0), [$phi_"ref"$], stroke: 0pt),
    edge((0.2, 0), <sub>, "-|>"),
    node((1, 0), [$  $], name: <sub>, shape: circle),
    edge((1, 0.8), <sub>, "-|>", label: $-$, label-side: left, label-pos: 0.8),
    node((1, 0.8), [$phi_"meas"$], stroke: 0pt),

    node((2, -1), [$k_i 1 / s$], name: <ki>, width: 5em, height: 3em),
    node((2, 0), [$k_p$], shape: rect, name: <kp>, width: 5em, height: 3em),
    node((2, 1), [$k_d s (N) / (s + N)$], name: <kd>, width: 5em, height: 3em),

    edge(<sub>, (1.3, 0), (1.3, -1), <ki>, "-|>"),
    edge(<sub>, <kp>, "-|>"),
    edge(<sub>, (1.3, 0), (1.3, 1), <kd>, "-|>"),

    edge(<ki>, (2.8, -1), <sum>, "-|>"),
    edge(<kp>, <sum>, "-|>"),
    edge(<kd>, (2.8, 1), <sum>, "-|>"),

    node((2.8, 0), [$  $], name: <sum>),

    edge("-|>", label: $tau_phi$),
  ),
  caption: [PID-Regelung einer Achse]
) <att_pid>

Die Parameter des PID-Reglers wurden zunächst in Simulation empirisch ermittelt und anschließend noch am realen System auf dem Teststand weiter optimiert. Die Ergebnisse sind in der folgenden Tabelle dargestellt:

#figure(table(
columns: (auto, auto, auto, auto, auto),
inset: 8pt,
align: center + horizon,
fill: (x, y) => if y == 0 or x == 0 { gray.lighten(80%) },
[], [$k_p$], [$k_i$], [$k_d$], [$N$],
[Roll], [$1.40$], [$1.18$], [$0.35$], [$100$],
[Pitch], [$1.42$], [$1.20$], [$0.38$], [$100$],
[Yaw], [$1.20$], [$0.70$], [$0.50$], [$100$]

), caption: [Empirisch ermittelte PID-Parameter für Lageregelung]) <pid_att>

Es ist zu erkennen, dass die Parameter für die Roll- und Nick-Achse relativ ähnlich sind. Dies lässt sich auf die strukturelle Symmetrie des Systems zurückführen. Bei der Gier-Achse fällt der P-Anteil trotz des höheren Trägheitsmomentes geringer aus, da hier kein destabilisierendes Moment kompensiert werden muss. Der geringere P-Anteil für die Gier-Achse trotz höherem Trägheitsmoment lässt sich damit erklären, dass es kein destabilisierendes Moment gibt, welches ausgeglichen werden muss. Auch der I-Anteil ist niedriger dimensioniert, da die Gier-Achse bereits inhärent ein integrierendes Verhalten aufweist. Dieser dient hier nur für eine Verstärkung dieses Verhaltens. Der D-Anteil ist hingegen höher, was sich mit der höheren Trägheit um diese Achse erklären lässt.
=== LQR mit integraler Ausgangsrückführung

Im Gegensatz zum klassischen PID-Regler basiert der Linear-Quadratische Regler (LQR) auf einer Zustandsrückführung anstelle einer reinen Ausgangsrückführung. Da im vorliegenden System lediglich die Euler-Winkel direkt gemessen werden können, müssen die zur vollständigen Zustandsbeschreibung notwendigen Winkelgeschwindigkeiten geschätzt werden. Hierzu wird ein Kalman-Filter eingesetzt @lunzeRegelungstechnik22016. Dieser wägt die Messgüte, also das Sensorrauschen, gegen die Modellgüte, also die Modellgenauigkeit, optimal ab, um eine statistisch optimale Zustandsschätzung zu liefern. Um die Komplexität gering zu halten, wird hierbei ein vereinfachtes Integratormodell anstelle der vollständigen Systemdynamik verwendet.

Um ein präzises Führungsverhalten sowie stationäre Genauigkeit zu gewährleisten, wird das System um einen Vorfilter $bold(S)$ und eine integrale Ausgangsrückführung erweitert. Daraus ergibt sich die folgende Systemstruktur:

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    // Eingang
    node((-0.3, 1), [$bold(eta)_"ref"$], stroke: 0pt, name: <in>),
    
    // Oberer Pfad (Feedforward)
    node((3.2, 0), [$bold(S)$], name: <s>, width: 3em, height: 2.5em),
    
    // Summationsstelle links
    node((1, 1), [$  $], name: <sum1>, shape: circle),
    
    // Mittlerer Pfad (I-Anteil)
    node((2, 1), diagram(node((0,0), [$1/s$], stroke: 0pt)), name: <int>, width: 4em, height: 2.5em),
    node((3.2, 1), [$-bold(K_i)$], name: <ki>, width: 3em, height: 2.5em),
    
    // Unterer Pfad (Feedback/Kalman)
    node((2, 2.2), [Kalmanfilter], name: <kal>, width: 7em, height: 2.5em),
    node((3.2, 2.2), [$-bold(K)$], name: <k>, width: 3em, height: 2.5em),
    
    // Summationsstelle rechts
    node((4.5, 1), [$  $], name: <sum2>, shape: circle),
    
    // Strecke / Modell
    node((6, 1), [Rotationsmodell], name: <model>, width: 9em, height: 3.5em),
    node((7.5, 1), [$bold(eta)$], stroke: 0pt, name: <out>),

    // Verbindungen
    edge((0.3, 1), (0.3, 0), <s>, "-|>"),
    edge((0.0, 1), <sum1>, "-|>"),
    
    edge(<sum1>, <int>, "-|>"),
    edge(<int>, <ki>, "-|>"),
    
    edge(<ki>, <sum2>, "-|>", label-side: left),
    edge(<s>, (4.5, 0), <sum2>, "-|>"),
    
    edge(<sum2>, <model>, "-|>"),
    edge(<model>, <out>, "-|>"),
    
    // Rückführung
    edge((6.8, 1), (6.8, 3.2), (1, 3.2), (1, 1.3), <sum1>, "-|>", label: [$-$], label-pos: 0.8),
    edge((1, 2.2), <kal>, "-|>"),
    edge(<kal>, <k>, "-|>"),
    edge(<k>, (4.5, 2.2), <sum2>, "-|>", label-side: left),
  ),
  caption: [Struktur des Zustandreglers mit integraler Ausgangsrückführung und Vorfilter]
) <system_diagram>

Da in dem System die einzelnen Achsen als entkoppelt betrachtet werden können, weist der LQR mit integraler Rückführung strukturell große Ähnlichkeiten zu drei separaten PID-Reglern auf. Der einzige Unterschied liegt in der Umsetzung des D-Anteils. Während dieser beim PID-Regler durch eine gefilterte numerische Differenzierung des Regelfehlers realisiert wird, nutzt der LQR die vom Kalman-Filter geschätzte Winkelgeschwindigkeit. Diese geht direkt in das Stellgesetz ein und das ohne die Ableitung der Führungsgröße.

Der entscheidende Vorteil ist deshalb wenig struktureller Natur, sondern resultiert primär aus der Methodik der Parameterbestimmung. Während der PID-Regler eine manuelle Abstimmung erfordert, erfolgt diese beim LQR durch eine mathematische Optimierung auf Basis des Systemmodells. Wenn die Modellgüte hinreichend genau ist wird beim LQR zusätzlich Stabilität garantiert.

Zur Bestimmung der Reglermatrizen $bold(K)$ und $bold(K)_i$ wird das Zustandsraummodell um die integrierten Fehler der Euler-Winkel $bold(x)_"I, r"$ erweitert. Das resultierende erweiterte System lautet:
$ d/(d t) vec(bold(x)_"r", bold(x)_"I, r") = mat(bold(A_"r"), bold(0); -bold(C)_"r", bold(0)) vec(bold(x)_"r", bold(x)_"I, r") + vec(bold(B), bold(0)) bold(tau_"ctrl") + vec(bold(0), bold(I)) bold(eta_"ref") $

Für dieses System sind die Gewichtungsmatrizen $bold(Q)$ und $bold(R)$ der Kostenfunktion so zu wählen, dass ein optimaler Kompromiss zwischen Regelgüte und Stellaufwand erzielt wird. In @okyereLQRControllerDesign2019 wird dabei Bryson's Regel für die initiale Wahl der Gewichtungsmatrizen angewandt. Diese besagt, dass die Matrizen als Diagonalmatrizen gewählt werden sollen, deren Einträge dem Kehrwert des Quadrats der maximal zulässigen Abweichungen entsprechen:
$ bold(Q) = "diag"(1 / max(bold(x)_"r, erw")^2), " " bold(R) = "diag"(1 / max(bold(tau)_"ctrl")^2) $

Als Grenzwerte wurden für die Euler-Winkel sowie deren integrierte Fehler jeweils 1° und für die Winkelgeschwindigkeit 5°/s definiert. Das Limit für die Stellgrößen wurde zunächst auf 0,03 Nm festgesetzt, da dies in etwa dem maximalen Moment bei einer Drosselung von 50 % entspricht, die den Motor nicht in den Sättigungsbereich treibt.

In Testläufen zeigte sich jedoch, dass die Stellgröße bei dieser Konfiguration dennoch häufig die Sättigungsgrenzen erreichte. Um den Linearitätsbereich der Motoren zu wahren, wurde die Gewichtung der Stellgröße letztlich um den Faktor 2,5 erhöht. Daraus ergeben sich gerundet die folgenden Gewichtungsmatrizen:

$ bold(Q) = "diag"(3300, 3300, 3300, 130, 130, 130, 3300, 3300, 3300) $
$ bold(R) = "diag"(2500, 2500, 2500) $

Da die Implementierung auf einem digitalen System erfolgt, muss das Optimierungsproblem für das diskretisierte Systemmodel $(bold(A)_"d", bold(B)_"d")$ gelöst werden. Hierzu wird zunächst die diskrete algebraische Riccati-Gleichung nach $bold(P)$ aufgelöst:
$ bold(P) = bold(A_"d")^top bold(P) bold(A_"d") - ( bold(A_"d")^top bold(P) bold(B_"d") ) (bold(R) + bold(B_"d")^T bold(P) bold(B_"d"))^(-1) (bold(B_"d")^top bold(P) bold(A_"d")) + bold(Q) $

Die optimale, erweiterte Reglermatrix $[bold(K), bold(K)_i]$ ergibt sich anschließend zu:
$ [bold(K), bold(K)_i] = (bold(R) + bold(B_"d")^top bold(P) bold(B_"d"))^(-1) bold(B_"d")^top bold(P) bold(A_"d") $

In MATLAB kann die Diskretierung des Systems und die Reglersynthese in einem Schritt mit dem Befehl `lqrd(A, B, Q, R, Ts)` durchgeführt werden. @LqrdDesignDiscrete

=== Evaluierung

Zur Evaluierung der Regelgüte wurden beide Algorithmen für jede Achse einzeln anhand einer einheitlichen Referenztrajektorie getestet. Diese Trajektorie umfasst Sprungantworten, Rampenfunktionen sowie harmonische Schwingungen, um ein breites Spektrum an Systemdynamiken abzudecken. 

Um die Leistungsfähigkeit der Regler zu quantifizieren, wurde die Wurzel des mittleren quadratischen Fehlers zwischen der Referenz und dem gemessenen Ausgang für jede Achse berechnet. Die Ergebnisse sind in der folgenden Tabelle dargestellt:

#figure(
  table(
    columns: (auto, auto, auto),
    inset: 8pt,
    align: center + horizon,
    fill: (x, y) => if y == 0 or x == 0 { gray.lighten(80%) },
    [Achse], [PID], [LQR],
    [Roll], [$1.93 degree$], [$1.71 degree$],
    [Nick], [$1.70 degree$], [$1.72 degree$],
    [Gier], [$0.90 degree$], [$1.75 degree$],
  ),
  caption: [Vergleich der Regelgüte zwischen PID- und LQR-Regler anhand des Root Mean Squared Error]
) <eval_att>

Wie bereits beim Reglerentwurf erläutert, weisen beide Strukturen eine hohe Ähnlichkeit auf. Ein wesentlicher Vorteil des LQR liegt jedoch in der Kombination mit dem Kalman-Filter. Da die Schätzung der Winkelgeschwindigkeit deutlich unempfindlicher gegenüber Messrauschen ist als die numerische Differenzierung des Fehlers mit Tiefpassfilter, erlaubt der LQR höhere D-Anteile, wodurch die Dynamik deutlich verbessert werden kann. Jedoch ließe sich auch der PID-Regler mit einem Kalman-Filter kombinieren, um die Vorteile der verbesserten Dämpfung zu nutzen. Somit ist dieser Vorteil nicht inhärent für die LQR-Struktur an sich.

Im Gegensatz dazu erlaubt der PID-Regler eine intuitivere manuelle Feinabstimmung, da die Parameter hier nicht durch das zugrunde liegende Systemmodell gegenseitig beschränkt werden. Im Gesamtergebnis performen beide Ansätze bezüglich des Gütekriteriums ähnlich, wobei der LQR auf der Roll-Achse eine leicht höhere Regelgüte erzielt. Auf der Gier-Achse hingegen überzeugt der PID-Regler, während der LQR hier ein deutlich schwächeres Ergebnis liefert.

#subfigures(
  columns: (auto),
  figure(
    show_plot(
      (
        ("plots/pid_roll.csv", (
          ([Referenz $phi.alt_"ref"$], 7),
          ([Ausgang $phi.alt$ mit PID-Regler], 1),
        )),
        ("plots/lqr_roll.csv", (
          ([Ausgang $phi.alt$ mit LQR-Regler], 1),
        )),
      ),
      [Roll-Winkel $phi.alt$ ($degree$)],
      y_limits: (-10, 17.0)
    ),
    caption: [Roll-Achse]
  ),
  figure(
    show_plot(
      (
        ("plots/pid_pitch.csv", (
          ([Referenz $theta_"ref"$], 8),
          ([Ausgang $theta$ mit PID-Regler], 2),
        )),
        ("plots/lqr_pitch.csv", (
          ([Ausgang $theta$ mit LQR-Regler], 2),
        )),
      ),
      [Nick-Winkel $theta$ ($degree$)],
      y_limits: (-10, 17.0)
    ),
    caption: [Nick-Achse]
  ),
  figure(
    show_plot(
      (
        ("plots/pid_yaw.csv", (
          ([Referenz $psi_"ref"$], 9),
          ([Ausgang $psi$ mit PID-Regler], 3),
        )),
        ("plots/lqr_yaw.csv", (
          ([Ausgang $psi$ mit LQR-Regler], 3),
        )),
      ),
      [Gier-Winkel $psi$ ($degree$)],
      y_limits: (-10, 17.0)
    ),
    caption: [Gier-Achse]
  ),
  caption: [Verhalten mit PID-Regler]
)

== Positionsregelung
=== PID
=== LQR mit integraler Ausgangsrückführung
=== Evaluierung


// - Bestimmung der Bandbreite meines Reglers -> Abtastrate sollte so 10-20 mal so schnell wie die Bandbreite sein

== Implementierung
