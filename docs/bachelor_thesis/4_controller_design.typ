#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge
#import "@preview/cetz:0.4.2": canvas
#import "@preview/cetz-plot:0.1.3": plot

#import "conf/conf-unia-rt.typ": runin, show_plot, subfigures, show_xy_plot



= Reglerentwurf

Quadrocopter sind inhärent instabile Systeme, da keine natürlichen Rückstellkräfte existieren, die äußeren Störungen entgegenwirken. Beispielsweise führt ein störendes Drehmoment um die Roll-Achse zu einer bleibenden Änderung der Winkelgeschwindigkeit, welche ohne aktiven Eingriff nur sehr langsam durch aerodynamischen Widerstand abgebaut würde. Während sich die Winkelgeschwindigkeit im freien Flug somit näherungsweise grenzstabil verhält, ist der Rollwinkel durch die Integration der Winkelgeschwindigkeit bereits instabil. @stephanMulticopterFlightControl2025 Auf dem verwendeten Teststand verschärft sich dieses Verhalten noch weiter, da hier bereits die Winkelgeschwindigkeit aufgrund des versetzten Schwerpunktes instabil ist. Analog dazu zeigt auch das translatorische Verhalten Instabilitäten. Dieses Systemverhalten macht eine aktive Regelung unumgänglich. Sie dient aber nicht nur der reinen Stabilisierung, sondern sorgt auch dafür, dass das System Trajektorien möglichst dynamisch folgen kann. 

Die implementierte Regelungsstruktur besteht aus drei Komponenten: die Positionsregelung, die Lageregelung und die Steuerungszuweisung (@control_overview). Wie auch in der Modellbildung wird die Regelung des Systems in rotatorisches und translatorisches Verhalten unterteilt. Diese Trennung ist in der Praxis als Standard etabliert, da sie mehrere Vorteile bietet: Zum einen reduziert sich die Komplexität der Reglersynthese, da der Lageregler unabhängig von der Positionsregelung entwickelt werden kann. Sobald der Lageregler die gewünschte Dynamik aufweist, kann darauf aufbauend der Positionsregler entwickelt werden. Zum anderen erlaubt es die Verwendung einer Kaskadenregelung. Das rotatorische Verhalten ist deutlich dynamischer als das translatorische und Lagedaten können mit höherer Frequenz gemessen werden als die Positionsdaten. Daher ist es sinnvoll, die Lageregelung getrennt in einer inneren Schleife mit höherer Taktfrequenz auszuführen. @quanIntroductionMulticopterDesign2017

#figure(
  diagram(
    node-stroke: 0.7pt,
    // spacing: 3em,
    label-sep: 0.2em,
    node-corner-radius: 5pt,
    
    // Nodes (Blocks) - Using explicit coordinates
    edge((0, -1), <pos>, "-|>", label: $x_"ref", y_"ref", z_"ref"$, label-side: right),
    node((0, 0), [Positionsregelung], name: <pos>),
    node((0.5, 1), [Lageregelung], name: <att>),
    node((0.25, 2), [Steuerungszuweisung ("Mixing")], name: <mixer>),
    edge((-0.2, 0), (-0.2, 2), "-|>", label: $F_"thrust"$, label-pos: 0.2, label-side: right),
    edge((0.65, -1), (0.65, 1), "-|>", label: $psi_"ref"$, label-pos: 0.2, label-side: left),
    edge((0.35, 0), (0.35, 1), "-|>", label: $phi.alt_"ref", theta_"ref"$, label-side: right),
    edge(<att>, (0.5, 2), "-|>", label: $bold(tau)_"ctrl"$),

    edge(<mixer>, (0.25, 3), "-|>", label: $bold(delta)$)
  ),
  caption: [Kaskadenstruktur der Regelung]
) <control_overview>

Als Führungsgrößen für den freien Flug dienen die Position $[x_"ref", y_"ref", z_"ref"]^top$ sowie der Gierwinkel $psi_"ref"$. Der Regler berechnet daraus den Stellgrößenvektor $bold(delta) = [delta_1, delta_2, delta_3, delta_4]^top$, welcher die Ansteuerung der vier Motoren definiert.

Im Folgenden werden die drei Kernkomponenten der Regelungsstruktur detailliert erläutert. Für die Positions- sowie die Lageregelung wird zunächst ein modellunabhängiger PID-Regler vorgestellt. Dieser dient als Referenz, um die Leistungsfähigkeit des modellbasierten LQ-Reglers vergleichend zu bewerten. Abschließend wird die Vorgehensweise zur Implementierung der Algorithmen auf dem Zielsystem dargelegt.

== Steuerungszuweisung <control_alloc>

Die Aufgabe der Steuerungszuweisung besteht darin, die von den Reglern geforderten Kräfte und Momente in die Stellbefehle für die einzelnen Motoren umzuwandeln. Im Kontext von Multicoptern wird dies auch häufig als Mixing bezeichnet. Da sowohl die Steuerungseffektivitätsmatrix $bold(B)_"eff"$ (vgl. @b_eff) als auch der Antriebszusammenhang (vgl. @thrust) invertierbar sind, lassen sich die Stellgrößen direkt berechnen. Es gilt:

$ vec(f_"1, ref", f_"2, ref", f_"3, ref", f_"4, ref") = bold(B)_"eff"^(-1) vec(F_"thrust", tau_x, tau_y, tau_z) $
$ delta_"i, ref" = sqrt(f_"i, ref" / a) + b $

Der Arbeitsbereich eines Motors liegt bei einer Drosselung zwischen $15 %$ und $90 %$. Eine einfache Limitierung der einzelnen Stellgrößen $delta_i$ ist jedoch problematisch: Tritt ein Motor in die Sättigung, ändert sich nicht nur die Amplitude der Schubkraft, sondern insbesondere die Richtung des Momentvektors. Dies führt zu Kopplungen in andere Freiheitsgrade, die vom Regler nicht vorgesehen sind. Damit ist die Stabilität des Gesamtsystems gefährdet. 

Um dieses Problem zu lösen, müssen bereits die verallgemeinerten Stellgrößen $bold(u)$ (@b_eff) begrenzt werden. Dies ist mathematisch anspruchsvoll, da die Begrenzung nicht für jede Komponente isoliert, sondern in Abhängigkeit der Gesamtsumme und unter Beibehaltung der Richtung des Drehmomentvektors erfolgen muss. Zusätzlich wird meist der Lagestabilität eine höhere Bedeutung im Vergleich zum Erhalt der Höhe beigemessen, was ebenfalls bei der Steuerungszuweisung beachtet werden muss. Auf diesen Zusammenhang wird in @quanIntroductionMulticopterDesign2017 genauer eingegangen.
Wird der Quadrocopter jedoch mit einer Schubkraft von ca. 50 % und mit geringer Dynamik betrieben, werden die Sättigungsbereiche selten erreicht. Da dies bei dem untersuchten System als Vorraussetzung fesgesetzt werden kann, werden in dieser Arbeit die Motorstellgrößen trotz der genannten Problematik direkt limitiert. Sollten dadurch kurzzeitige Sättigungseffekte auftreten, müssen die Regler robust genug sein, um die dadurch entstehenden Störmomente schnell auszugleichen. 

== Lageregelung

Wie bereits zu Beginn des Kapitels erläutert wurde, ist das Rotationsverhalten inhärent instabil und muss stabilisiert werden. Da das System nahe der Ruhelage betrieben werden soll, liefert das in @lin_model entwickelte linearisierte Rotationsmodell hier eine gute Approximation. Aus diesem geht hervor, dass die einzelnen Achsen in der Nähe der Ruhelage als entkoppelt betrachtet werden können. Deshalb ist es möglich, die Regler für die einzelnen Achsen getrennt voneinander zu entwickeln.

Das Übertragungsverhalten einer einzelnen Achse entspricht einem System 2. Ordnung, bei dem die Stellgröße direkt auf die Beschleunigung des Orientierungswinkels wirkt. Um einen geeigneten Regler zu entwerfen, wird das linearisierte Verhalten am Beispiel der Roll-Achse auf dem Teststand genauer betrachtet. @lin_rot_dynamic in der Teststandskonfiguration lässt sich zu folgendem Zusammenhang umformen:

$ dot.double(phi.alt) = 1 / J_"xx" (-p_x dot(phi.alt) + m g h phi.alt + tau_x) $

Unter Verwendung des allgemeinen Regelgesetzes $ tau_x = - k_p phi.alt - k_d dot(phi.alt) $ lässt sich das System als homogene Differentialgleichung zweiter Ordnung darstellen und kann in
$ dot.double(y) = - a_1 dot(y) - a_0 y $
überführt werden.

Solche idealen Systeme sind asymptotisch stabil, wenn $a_0, a_1 > 0$ @quanIntroductionMulticopterDesign2017. Diese Bedingung ließe sich bereits durch einen reinen P-Regler erfüllen. In diesem Fall wäre die Dämpfung jedoch allein durch aerodynamische Effekte gegeben und somit sehr gering, was zu einer hohen Schwingung des Systems führen wird. Außerdem vernachlässigt das idealisierte Modell zusätzliche verzögernde Faktoren, die das reale System trotzdem destabilisieren würden. Dazu gehören Aktorverzögerungen, Abtastzeiten des diskreten Reglers und Totzeiten in der Sensordatenverabeitung.
Durch die Hinzunahme eines D-Anteils kann die Phasenreserve erhöht und die Systemantwort gedämpft werden, wodurch auch das reale System zuverlässig stabilisiert wird.

Das System besitzt im Betrieb auf dem Teststand kein integrierendes Verhalten, da $a_0 != 0$ aufgrund des versetzten Schwerpunkts gilt. Deshalb benötigt dieses zwingend einen I-Anteil, um stationäre Genauigkeit zu erreichen. In freifliegender Konfiguration könnte hingegen theoretisch auf den I-Anteil verzichtet werden, da hier $a_0 = 0$ gilt und das System damit bereits ein integrierendes Verhalten aufweist. Jedoch ist auch hier ein I-Anteil meist sinnvoll, um die stationäre Genauigkeit zu verbessern. Bei der Verwendung eines I-Anteils muss beachtet werden, dass dieser eine zusätzliche Verzögerung in das System bringt, was die Phasenreserve verringert und damit die Stabilität gefährden kann. Deshalb muss die Verstärkung des I-Anteils sorgfältig gewählt werden, um einen guten Kompromiss zwischen Regelgüte und Stabilität zu erreichen. @lunzeRegelungstechnik1Systemtheoretische2020

// Die Lagedaten können vom DMP mit lediglich 200 Hz abgefragt werden. Aus diesem Grund ist eine Regelrate von ebenfalls 200 Hz sinnvoll.
// Dies führt zusätzliche Verzögerung in das System ein und begrenzt die Dynamik, wenn gleichzeitig Stabilität gewährleistet werden soll. In der Praxis der Regelungstechnik gilt als bewährte Faustregel, dass die Regelfrequenz etwa 10- bis 20-mal höher sein sollte als die gewünschte Bandbreite des geschlossenen Regelkreises. Dadurch kann der Regler also Schwingungen oder Störungen gut ausgleichen, die langsamer als 10 - 20 Hz sind, bzw. auch Trajektorien gut folgen, die diese Frequenzen aufweisen. 

=== PID-Regelung

Die einfachste Methode, um einen Regler mit solchen Eigenschaften umzusetzen ist der PID-Regler (@att_pid). Dieser wendet die proportionalen, integralen und derivativen Anteile direkt auf die Regelabweichung $e = w - y$ an, wodurch automatisch eine Folgeregelung realisiert wird @lunzeRegelungstechnik1Systemtheoretische2020. Um die Verstärkung von hochfrequentem Messrauschen zu begrenzen, wird ein realer D-Anteil mit einem Tiefpassfilter $G(s) = N / (s+N)$ verwendet. Dieser dämpft hohe Amplituden im D-Anteil, die durch den Differenzenquotienten entstehen und das System destabilisieren könnten.

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    edge-corner-radius: none,
    spacing: 3em,

    node((-0.15, 0), [$w$], stroke: 0pt),
    edge((-0.15, 0), <sub>, "-|>"),
    node((0.7, 0), [$  $], name: <sub>, shape: circle),
    edge((0.7, 0.6), <sub>, "-|>", label: $-$, label-side: left, label-pos: 0.8),
    node((0.7, 0.6), [$y$], stroke: 0pt),

    node((2, -1), [$k_i 1 / s$], name: <ki>, width: 5em, height: 3em),
    node((2, 0), [$k_p$], shape: rect, name: <kp>, width: 5em, height: 3em),
    node((2, 1), [$k_d s (N) / (s + N)$], name: <kd>, width: 5em, height: 3em),

    edge(<sub>, (1.3, 0), (1.3, -1), <ki>, "-|>"),
    edge(<sub>, <kp>, "-|>", label: $e$, label-side: left, label-pos: 0.2),
    edge(<sub>, (1.3, 0), (1.3, 1), <kd>, "-|>"),

    edge(<ki>, (2.8, -1), <sum>, "-|>"),
    edge(<kp>, <sum>, "-|>"),
    edge(<kd>, (2.8, 1), <sum>, "-|>"),

    node((2.8, 0), [$  $], name: <sum>),

    edge("-|>", label: $u$),
  ),
  caption: [Realer PID-Regler]
) <att_pid>

Für die vollständige Lageregelung werden drei reale PID-Regler wie folgt kombiniert:
#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    node((0, 0), [$phi.alt_"ref"$], stroke: 0pt, name: <x_ref>),
    edge("-|>"),
    node((1, 0), " ", shape: circle, name: <sum1>),
    edge("-|>", label: $e_phi.alt$, label-side: left, label-pos: 0.9),
    node((4, 0), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 0), [$tau_"ctrl,x"$], stroke: 0pt, name: <tau_ctrl_y>),
    node((1, 3), [$phi.alt_"meas"$], stroke: 0pt, name: <x_meas>),
    edge("-|>", <sum1>, label: $-$, label-side: left, label-pos: 0.95),

    node((0, 1), [$theta_"ref"$], stroke: 0pt, name: <y_ref>),
    edge("-|>"),
    node((2, 1), " ", shape: circle, name: <sum2>),
    edge("-|>", label: $e_theta$, label-side: left, label-pos: 0.8),
    node((4, 1), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 1), [$tau_"ctrl,y"$], stroke: 0pt, name: <tau_ctrl_x>),
    node((2, 3), [$theta_"meas"$], stroke: 0pt, name: <y_meas>),
    edge("-|>", <sum2>, label: $-$, label-side: left, label-pos: 0.92),

    node((0, 2), [$psi_"ref"$], stroke: 0pt, name: <z_ref>),
    edge("-|>"),
    node((3, 2), " ", shape: circle, name: <sum3>),
    edge("-|>", label: $e_psi$, label-side: left),
    node((4, 2), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 2), [$tau_"ctrl,z"$], stroke: 0pt, name: <F_t>),
    node((3, 3), [$psi_"meas"$], stroke: 0pt, name: <z_meas>),
    edge("-|>", <sum3>, label: $-$, label-side: left, label-pos: 0.75),
  ),
  caption: [Struktur der Lageregelung mit PID-Reglern]
)

Die Regelparameter wurden empirisch ermittelt, indem sie zunächst in Simulation optimiert und anschließend am realen System auf dem Teststand präzisiert wurden. Die Ergebnisse sind in der folgenden Tabelle dargestellt:

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

Im Gegensatz zum klassischen PID-Regler basiert der Linear-Quadratische Regler (LQR) auf einer Zustandsrückführung anstelle einer reinen Ausgangsrückführung. Da im vorliegenden System lediglich die Euler-Winkel direkt gemessen werden können, müssen die zur vollständigen Zustandsbeschreibung notwendigen Winkelgeschwindigkeiten geschätzt werden. Hierzu wird ein Kalman-Filter eingesetzt @lunzeRegelungstechnik22016. Dieser wägt das Sensorrauschen gegen die Modellgenauigkeit optimal ab, um eine statistisch optimale Zustandsschätzung zu liefern. Um die Komplexität gering zu halten, wird ein vereinfachtes Integratormodell anstelle der vollständigen Systemdynamik verwendet.

Ein präzises Führungsverhalten sowie stationäre Genauigkeit lassen sich durch Erweiterung des Systems um einen Vorfilter
$ bold(S) = -(bold(C)(bold(A)-bold(B)bold(K))^(-1) bold(B))^(-1) $ 
und eine integrale Ausgangsrückführung erreichen @lunzeRegelungstechnik22016. Daraus ergibt sich die folgende Regelungsstruktur:

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    // Eingang
    node((-0.3, 1), [$bold(eta)_"ref"$], stroke: 0pt, name: <in>),
    
    // Oberer Pfad (Feedforward)
    node((4.0, 0), [$bold(S)$], name: <s>, width: 3em, height: 2.5em),
    
    // Summationsstelle links
    node((1, 1), [$  $], name: <sum1>, shape: circle),
    
    // Mittlerer Pfad (I-Anteil)
    node((2, 1), diagram(node((0,0), [$1/s$], stroke: 0pt)), name: <int>, width: 4em, height: 2.5em),
    node((4.0, 1), [$-bold(K_i)$], name: <ki>, width: 3em, height: 2.5em),
    
    // Unterer Pfad (Feedback/Kalman)
    node((2, 2.2), [Kalmanfilter], name: <kal>, width: 7em, height: 2.5em),
    node((4.0, 2.2), [$-bold(K)$], name: <k>, width: 3em, height: 2.5em),
    
    // Summationsstelle rechts
    node((5.3, 1), [$  $], name: <sum2>, shape: circle),

    // Verbindungen
    edge((0.3, 1), (0.3, 0), <s>, "-|>"),
    edge((0.0, 1), <sum1>, "-|>"),
    
    edge(<sum1>, <int>, "-|>", label: $bold(e)_bold(eta)$),
    edge(<int>, <ki>, "-|>"),
    
    edge(<ki>, <sum2>, "-|>", label-side: left),
    edge(<s>, (5.3, 0), <sum2>, "-|>"),

    edge(<sum2>, (6.8, 1), "-|>"),
    node((6.8, 1), [$bold(tau)_"ctrl"$], stroke: 0pt),
    
    // Rückführung
    node((-0.3, 2.2), [$bold(eta)_"meas"$], stroke: 0pt),

    edge((0, 2.2), (1, 2.2), (1, 1.3), <sum1>, "-|>", label: [$-$], label-pos: 0.8),
    edge((1, 2.2), <kal>, "-|>"),
    edge(<kal>, <k>, "-|>", label: $[bold(hat(eta)), bold(hat(omega))]^top$),
    edge(<k>, (5.3, 2.2), <sum2>, "-|>", label-side: left),
  ),
  caption: [Struktur der Lageregelung mit LQR, Vorfilter und integraler Ausgangsrückführung]
)

Da in dem System die einzelnen Achsen als entkoppelt betrachtet werden können, weist der LQR mit integraler Rückführung strukturell große Ähnlichkeiten zu drei separaten PID-Reglern auf. Der einzige Unterschied liegt in der Umsetzung des D-Anteils. Während dieser beim PID-Regler durch eine gefilterte numerische Differenzierung des Regelfehlers realisiert wird, nutzt der LQR die vom Kalman-Filter geschätzte Winkelgeschwindigkeit. Diese geht direkt und ohne die Ableitung der Führungsgröße in das Regelgesetz mit ein. Der entscheidende Vorteil ist deshalb weniger struktureller Natur, sondern resultiert primär aus der Methodik der Parameterbestimmung. Während der PID-Regler eine manuelle Abstimmung erfordert, erfolgt diese beim LQR durch eine mathematische Optimierung auf Basis des Systemmodells. Wenn die Modellgüte hinreichend genau ist, wird beim LQR zusätzlich Stabilität garantiert.

Zur Bestimmung der Reglermatrizen $bold(K)$ und $bold(K)_i$ wird das Zustandsraummodell um die integrierten Fehler der Euler-Winkel $bold(x)_"I,r"$ erweitert. Das resultierende erweiterte System lautet:
$ d/(d t) vec(bold(x)_"r", bold(x)_"I,r") = mat(bold(A)_"r", bold(0); -bold(C)_"r", bold(0)) vec(bold(x)_"r", bold(x)_"I,r") + vec(bold(B), bold(0)) bold(tau)_"ctrl" + vec(bold(0), bold(I)) bold(eta)_"ref" $

Für dieses System sind die Gewichtungsmatrizen $bold(Q)$ und $bold(R)$ der Kostenfunktion
$ 
  J = integral_0^infinity bold(x)^top bold(Q) bold(x) + bold(u)^top bold(R) bold(u) "dt"
$
so zu wählen, dass ein optimaler Kompromiss zwischen Regelgüte und Stellaufwand erzielt wird. In @okyereLQRControllerDesign2019 wird dabei Bryson's Regel für die initiale Wahl der Gewichtungsmatrizen angewandt. Diese besagt, dass die Matrizen als Diagonalmatrizen gewählt werden sollen, deren Einträge dem Kehrwert des Quadrats der maximal zulässigen Abweichungen entsprechen:
$ bold(Q) = "diag"(1 / max(bold(x)_"r,erw")^2), " " bold(R) = "diag"(1 / max(bold(tau)_"ctrl")^2) $

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

Zur Evaluierung der Regelgüte wurden beide Algorithmen für jede Achse einzeln anhand einer einheitlichen Referenztrajektorie validiert. Um ein breites Spektrum an Systemdynamiken abzudecken, umfasst diese Trajektorie Sprungfunktionen, Rampen sowie harmonische Schwingungen. Das resultierende Systemverhalten der verschiedenen Achsen ist für beide Reglerkonzepte in @att_plots gegenübergestellt.

Wie bereits im Entwurf dargelegt, weisen beide Strukturen eine hohe Ähnlichkeit auf. Ein wesentlicher Vorteil des LQR liegt jedoch in der Kombination mit dem Kalman-Filter. Da die Schätzung der Winkelgeschwindigkeit deutlich unempfindlicher gegenüber Messrauschen ist als die numerische Differenzierung des Fehlers mittels Tiefpassfilter, erlaubt der LQR höhere D-Anteile, wodurch die Dynamik deutlich verbessert werden kann. Jedoch ließe sich auch der PID-Regler mit einem Kalman-Filter kombinieren, um die Vorteile der verbesserten Dämpfung zu nutzen. Somit ist dieser Vorteil nicht direkt der LQR-Struktur zuzuschreiben.
Im Gegensatz dazu erlaubt der PID-Regler eine intuitivere manuelle Feinabstimmung, da die Parameter hier nicht durch das zugrunde liegende Systemmodell gegenseitig beschränkt werden. 

Zur Quantifizierung der Leistungsfähigkeit wurde die Wurzel des mittleren quadratischen Fehlers (RMSE) zwischen der Referenz und dem gemessenen Ausgang für jede Achse berechnet (vgl. @eval_att). Im Gesamtergebnis performen beide Ansätze bezüglich des Gütekriteriums ähnlich, wobei der LQR auf der Roll-Achse eine leicht höhere Regelgüte erzielt. Auf der Gier-Achse hingegen überzeugt der PID-Regler, während der LQR hier ein deutlich schwächeres Ergebnis liefert.

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
  caption: [Vergleich der Regelgüte zwischen PID- und LQ-Regler anhand eines RMSE]
) <eval_att>

#figure(
  stack(
  show_plot(
    (
      ("plots/pid_roll.csv", (
        ([Referenz $phi.alt_"ref"$], 7),
        ([Ausgang $phi.alt$ mit PID-Regler], 1),
      )),
      ("plots/lqr_roll.csv", (
        ([Ausgang $phi.alt$ mit LQ-Regler], 1),
      )),
    ),
    [Roll-Winkel $phi.alt$ ($degree$)],
    y_limits: (-10, 17.0)
  ),
  show_plot(
    (
      ("plots/pid_pitch.csv", (
        ([Referenz $theta_"ref"$], 8),
        ([Ausgang $theta$ mit PID-Regler], 2),
      )),
      ("plots/lqr_pitch.csv", (
        ([Ausgang $theta$ mit LQ-Regler], 2),
      )),
    ),
    [Nick-Winkel $theta$ ($degree$)],
    y_limits: (-10, 17.0)
  ),
  show_plot(
      (
        ("plots/pid_yaw.csv", (
          ([Referenz $psi_"ref"$], 9),
          ([Ausgang $psi$ mit PID-Regler], 3),
        )),
        ("plots/lqr_yaw.csv", (
          ([Ausgang $psi$ mit LQ-Regler], 3),
        )),
      ),
      [Gier-Winkel $psi$ ($degree$)],
      y_limits: (-10, 17.0)
    ),
  
  ),
  caption: [Vergleich der rotatorischen Trajektorienfolge zwischen PID- und LQ-Regler]
) <att_plots>

== Positionsregelung
Die Positionsregelung bildet den äußeren Regelkreis, der die Sollwerte für die Roll- und Nickwinkel sowie den Gesamtschub vorgibt. Da sich das translatorische System im Schwebeflug, wie auch schon die rotatorische Dynamik, nahezu wie ein entkoppeltes, lineares System zweiter Ordnung verhält, ähnelt die Regelungsstruktur stark der Lageregelung. Um eine hohe Dämpfung, Stabilität und stationäre Genauigkeit zu gewährleisten, kommen neben dem Proportionalanteil auch ein Differenzial- (D) und ein Integralanteil (I) zum Einsatz. Die Umsetzung erfolgt analog zur Lageregelung entweder mit drei PID-Reglern oder einem LQR mit integraler Ausgangsrückführung.

#runin[Vorsteuerung]
Im Arbeitspunkt des Schwebeflugs muss die Schubkraft die Gewichtskraft exakt kompensieren. Es gilt:
$  F_"t,0" = m g $
Würde der Ausgleich der Gewichtskraft ausschließlich durch den I-Anteil des Reglers erfolgen, würde sich der Schub nur langsam aufbauen. Um dies zu verhindern, wird die statische Kraft $F_"t,0"$ als Vorsteuerung direkt auf das Stellsignal addiert.

#runin[Lageregler als innere Schleife]
Die Positionsdaten werden im System mit einer Frequenz von $50 "Hz"$ erfasst, während die Lageregelung mit $200 "Hz"$ arbeitet. Für eine gute Kaskadenregelung sollte die innere Schleife aus Sicht des äußeren Regelkreises näherungsweise als statisches System agieren. Als Faustregel gilt hierbei, dass die Taktrate des inneren Regelkreises etwa das Zehnfache der Äußeren betragen sollte. Die daraus resultierende ideale Taktrate von 500 Hz für die Lageregelung ist technisch jedoch nicht realisierbar, da die gefilterten Daten des DMP mit maximal 200 Hz ausgelesen werden können. Um trotz dieser Einschränkung eine hohe Regelgüte zu erzielen, wurde die Dynamik des inneren Kreises durch eine Reduzierung des I-Anteils erhöht. Dies geht zwar zulasten der stationären Genauigkeit der Lageregelung, ist jedoch unkritisch, da die übergeordnete Positionsregelung über einen eigenen I-Anteil verfügt, der die stationäre Genauigkeit im Gesamtsystem sicherstellt. Für eine bessere Vergleichbarkeit der Positionsregler wurde einheitlich ein PID-Lageregler (Parameter siehe @pid_att) mit halbierter I-Verstärkung eingesetzt.


#runin[Gesamtüberblick des Kaskadenregelkreises]
Die beiden Regelkreise werden wie in @cascaded_control gezeigt in einer Kaskade zusammengeschalten. Zusätzlich wird eine Sättigung dazwischengeschalten, welche $F_t$ auf max. $15 "N"$ begrenzt, und die Roll- und Nickwinkel auf max. $5 degree$ limitiert. Dies ist als Sicherheit gedacht, um bei unerwarteten Störungen oder einem zu dynamisch ausgelegten Regler nicht die Stabilität zu gefährden und einen Absturz zu vermeiden. 

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    edge((-0.3, 0.05), (1, 0.05), "-|>", label: $bold(p)_"ref"$),
    edge((-0.3, 0.35), (1, 0.35), "-|>", label: $bold(p)_"meas"$),
    node((1, 0.2), [Positionsregler], height: 4em),
    edge("-|>"),
    node((1.8, 0.2), " ", shape: circle),
    node((1.8, -1), [Vorsteuerung]),
    edge((1.8, -1), (1.8, 0.2), "-|>"),
    edge((1.8, 0.2), (2.6, 0.2), "-|>"),

    node((2.6, 0.2), "Sättigung", height: 2.5em),

    edge((2.6, 0.2), (5.0, 0.2), "-|>", label: $F_"t"$, label-pos: 0.85),

    edge((2.6, 0.2), (2.6, 0.95), (3.6, 0.95), "-|>", label: $phi.alt_"ref", theta_"ref"$, label-pos: 0.3),

    edge((2.0, 1.2), (3.6, 1.2), "-|>", label: $psi_"ref"$, label-pos: 0.15),
    edge((2.0, 1.45), (3.6, 1.45), "-|>", label: $bold(eta)_"meas"$, label-pos: 0.2),

    node((3.6, 1.2), "PID-Lageregler", height: 5em),
    edge((3.6, 1.2), (5.0, 1.2), "-|>", label: $bold(tau)_"ctrl"$),

    node((5.0, 0.7), "Mixing", height: 12em),
    edge("-|>", label: $bold(delta)$),
  ),
  caption: [Kaskadenregelung mit Positionsregelung als äußerem und Lageregelung als innerem Regelkreis]
) <cascaded_control>

=== PID-Regelung

Der PID-Regler einer Achse wird wie in der Lageregelung als reale PID-Regelung (vgl. @att_pid) umgesetzt. Bei der Implementierung müssen die spezifischen Vorzeichen und physikalischen Zusammenhänge zwischen der Reglerabweichung und der resultierenden Stellgröße berücksichtigt werden. So erfordert beispielsweise die Korrektur einer positiven Positionsabweichung in $x$-Richtung ein negatives Nick-Moment, während eine positive Abweichung in $y$-Richtung ein positives Roll-Moment verlangt. Diese Zusammenhänge sowie die Zuordnung der Ausgangsgrößen sind in der folgenden Abbildung schematisch dargestellt:

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    node((0, 0), [$x_"ref"$], stroke: 0pt, name: <x_ref>),
    edge("-|>"),
    node((1, 0), " ", shape: circle, name: <sum1>),
    edge("-|>"),
    node((4, 0), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 0), [$theta_"ref"$], stroke: 0pt, name: <tau_ctrl_y>),
    node((1, 3), [$x_"meas"$], stroke: 0pt, name: <x_meas>),
    edge("-|>", <sum1>, label: $-$, label-side: left, label-pos: 0.95),

    node((0, 1), [$y_"ref"$], stroke: 0pt, name: <y_ref>),
    edge("-|>", label: $-$, label-side: left, label-pos: 0.88),
    node((2, 1), " ", shape: circle, name: <sum2>),
    edge("-|>"),
    node((4, 1), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 1), [$phi.alt_"ref"$], stroke: 0pt, name: <tau_ctrl_x>),
    node((2, 3), [$y_"meas"$], stroke: 0pt, name: <y_meas>),
    edge("-|>", <sum2>),

    node((0, 2), [$z_"ref"$], stroke: 0pt, name: <z_ref>),
    edge("-|>"),
    node((3, 2), " ", shape: circle, name: <sum3>),
    edge("-|>"),
    node((4, 2), [Realer PID], name: <pid>, width: 7em, height: 2.5em),
    edge("-|>"),
    node((5, 2), [$F_"t"$], stroke: 0pt, name: <F_t>),
    node((3, 3), [$z_"meas"$], stroke: 0pt, name: <z_meas>),
    edge("-|>", <sum3>, label: $-$, label-side: left, label-pos: 0.75),
  ),
  caption: [Struktur der Positionsregelung mit PID-Reglern]
)

Auch hier wurden die Parameter experimentell in Simulation ermittelt und anschließend am realen System weiter optimiert. Die Ergebnisse sind in der folgenden Tabelle dargestellt:
#figure(table(
columns: (auto, auto, auto, auto, auto),  
inset: 8pt,
align: center + horizon,
fill: (x, y) => if y == 0 or x == 0 { gray.lighten(80%) },
[], [$k_p$], [$k_i$], [$k_d$], [$N$],
[X], [$0.3$], [$0.3$], [$0.4$], [$10$],
[Y], [$0.3$], [$0.3$], [$0.4$], [$10$],
[Z], [$2.5$], [$4.0$], [$3.8$], [$10$]
), caption: [Empirisch ermittelte PID-Parameter für die Positionsregelung]) <pid_pos>

=== LQR mit integraler Ausgangsrückführung
Da der LQR auf dem Systemmodell aufbaut und dieses bereits die physikalischen Zusammehänge enthält, ist die Positionsregelung von der Struktur exakt dieselbe wie auch bei der Lageregelung. Hier müssen ebenfalls die Geschwindigkeiten mit einem Kalman-Filter geschätzt werden, da nur die Positionen gemessen werden können. Auch die Vorfilterung der Führungsgrößen erfolgt analog zur Lageregelung, um ein präzises Führungsverhalten zu gewährleisten.

#figure(
  diagram(
    node-stroke: 0.7pt,
    label-sep: 0.2em,
    spacing: 1.8em,
    edge-corner-radius: 0pt,

    // Eingang
    node((-0.3, 1), [$bold(p)_"ref"$], stroke: 0pt, name: <in>),
    
    // Oberer Pfad (Feedforward)
    node((4.0, 0), [$bold(S)$], name: <s>, width: 3em, height: 2.5em),
    
    // Summationsstelle links
    node((1, 1), [$  $], name: <sum1>, shape: circle),
    
    // Mittlerer Pfad (I-Anteil)
    node((2, 1), diagram(node((0,0), [$1/s$], stroke: 0pt)), name: <int>, width: 4em, height: 2.5em),
    node((4.0, 1), [$-bold(K_i)$], name: <ki>, width: 3em, height: 2.5em),
    
    // Unterer Pfad (Feedback/Kalman)
    node((2, 2.2), [Kalmanfilter], name: <kal>, width: 7em, height: 2.5em),
    node((4.0, 2.2), [$-bold(K)$], name: <k>, width: 3em, height: 2.5em),
    
    // Summationsstelle rechts
    node((5.3, 1), [$  $], name: <sum2>, shape: circle),

    // Verbindungen
    edge((0.3, 1), (0.3, 0), <s>, "-|>"),
    edge((0.0, 1), <sum1>, "-|>"),
    
    edge(<sum1>, <int>, "-|>", label: $bold(e)_bold(p)$),
    edge(<int>, <ki>, "-|>"),
    
    edge(<ki>, <sum2>, "-|>", label-side: left),
    edge(<s>, (5.3, 0), <sum2>, "-|>"),

    edge(<sum2>, (6.8, 1), "-|>"),
    node((6.8, 1), [$[F_"t", phi.alt, theta]^top$], stroke: 0pt),
    
    // Rückführung
    node((-0.3, 2.2), [$bold(p)_"meas"$], stroke: 0pt),

    edge((0, 2.2), (1, 2.2), (1, 1.3), <sum1>, "-|>", label: [$-$], label-pos: 0.8),
    edge((1, 2.2), <kal>, "-|>"),
    edge(<kal>, <k>, "-|>", label: $[bold(hat(p)), bold(hat(v))]^top$),
    edge(<k>, (5.3, 2.2), <sum2>, "-|>", label-side: left),
  ),
  caption: [Struktur der Positionsregelung mit LQR, Vorfilter und integraler Ausgangsrückführung]
)

Die Parameterbestimmung erfolgt ebenfalls nach derselben Methodik, wobei die Gewichtungsmatrizen an die neuen Führungs- und Stellgrößen angepasst werden müssen. Als zulässige Maximalabweichung für die drei Positionskomponenten sowie für die Geschwindigkeit wurde ein Wert von $0,1 "m"$ bzw. $0,1 "m/s"$ gewählt. Das maximale Integral der Positionsabweichung wurde initial ebenfalls auf $0,1 "m" "s"$ festgelegt. Erste Testläufe verdeutlichten jedoch, dass die stationäre Genauigkeit eine stärkere Gewichtung erfordert, weshalb der entsprechende Wert in der Kostenmatrix verdoppelt wurde. Bei den Stellgrößen wurden die maximalen Winkel zunächst auf $5 degree$ limitiert, was jedoch zu starken Oszillationen führte. In der finalen Parametrierung wurde die maximale Stellgröße für die Gewichtungsmatrix daher auf $1 degree$ reduziert. Dies ist physikalisch plausibel, da bereits eine Neigung von $1 degree$ aus dem Schwebeflug (Hover) eine translatorische Beschleunigung von etwa $0,17 "m" "s"^(-2)$ induziert. Da die Vorsteuerung im Schwebeflug bereits die Gewichtskraft kompensiert, konnte die zusätzliche Schubkraft auf $0,5 "N"$ begrenzt werden. Bei einer Masse von ca. $1 "kg"$ entspricht dies einer zusätzlichen Beschleunigung von $0,5 "m" "s"^(-2)$. Daraus resultieren die folgenden Gewichtungsmatrizen:
$ bold(Q) = "diag"(100, 100, 100, 100, 100, 100, 200, 200, 200) $
$ bold(R) = "diag"(25, 3300, 3300) $



=== Evaluierung

Die Evaluierung der Positionsregelung erfolgt anhand einer zweidimensionalen Referenztrajektorie in Form eines Teils des "Hauses vom Nikolaus". Zur systematischen Überprüfung des Systemverhaltens werden drei Testreihen durchgeführt, bei denen jeweils ein translatorischer Freiheitsgrad konstant gehalten wird, während die übrigen zwei variiert werden (vgl. @eval_pos_plots). Dieser Pfad erlaubt eine detaillierte Analyse des Führungsverhalten: Während die vertikalen und horizontalen Segmente die isolierte Ansteuerung der einzelnen Achsen prüfen, dienen die diagonalen Bewegungen der Validierung der translatorischen Kopplung. 

Als Bewertungsmaß wurde der Root Mean Squared Error (RMSE) verwendet. Die Ergebnisse der Evaluierung bzgl. des RMSE sind in der folgenden Tabelle dargestellt. Hier zeigt sich, dass der PID-Regler in allen drei Achsen eine deutlich bessere Regelgüte erzielt als der LQR. Jedoch wurden die Parameter des LQR auch nicht weiter optimiert. Es ist daher nicht auszuschließen, dass durch eine gezielte Feinabstimmung der Gewichtungsmatrizen des LQR eine ähnliche Regelgüte erzielt werden könnte. Dennoch verdeutlichen die Ergebnisse, dass die theoretischen Vorteile des LQR in der Praxis nicht zwangsläufig zu einer besseren Regelgüte führen müssen, insbesondere wenn die Modellgenauigkeit begrenzt ist oder die Parameter nicht optimal gewählt wurden.
#figure(
  table(
    columns: (auto, auto, auto),
    inset: 8pt,
    align: center + horizon,
    fill: (x, y) => if y == 0 or x == 0 { gray.lighten(80%) },
    [Achse], [PID], [LQR],
    [XY], [$0.063 "m"$], [$0.118 "m"$],
    [XZ], [$0.049 "m"$], [$0.120 "m"$],
    [YZ], [$0.054 "m"$], [$0.127 "m"$],
  ),
  caption: [Vergleich der Regelgüte zwischen PID- und LQ-Regler anhand des Root Mean Squared Error]
) <eval_pos>

#figure(
  stack(
    spacing: 0.8em,
    show_xy_plot(
      (
        (
          path: "plots/pid_xy.csv", 
          series: (
            (label: [Referenz XY-Figur], x: 7, y: 8),
            (label: [Trajektorie mit PID-Regler], x: 4, y: 5),
          ),
        ),
        (
          path: "plots/lqr_xy.csv", 
          series: (
            (label: [Trajektorie mit LQ-Regler], x: 4, y: 5),
          ),
        ),
      ),
      x_label: [Position $x$ ($m$)],
      y_label: [Position $y$ ($m$)],
      y_limits: (-0.4, 1.1)
    ),
    show_xy_plot(
      (
        (
          path: "plots/pid_xz.csv", 
          series: (
            (label: [Referenz XZ-Figur], x: 7, y: 9),
            (label: [Trajektorie mit PID-Regler], x: 4, y: 6),
          ),
        ),
        (
          path: "plots/lqr_xz.csv", 
          series: (
            (label: [Trajektorie mit LQ-Regler], x: 4, y: 6),
          ),
        ),
      ),
      x_label: [Position $x$ ($m$)],
      y_label: [Position $z$ ($m$)],
      y_limits: (0.3, 1.8)
    ),
    show_xy_plot(
      (
        (
          path: "plots/pid_yz.csv", 
          series: (
            (label: [Referenz YZ-Figur], x: 8, y: 9),
            (label: [Trajektorie mit PID-Regler], x: 5, y: 6),
          ),
        ),
        (
          path: "plots/lqr_yz.csv", 
          series: (
            (label: [Trajektorie mit LQ-Regler], x: 5, y: 6),
          ),
        ),
      ),
      x_label: [Position $x$ ($m$)],
      y_label: [Position $y$ ($m$)],
      y_limits: (0.3, 1.8)
    ),
  ),
  caption: [Vergleich des Systemverhaltens mit PID- und LQ-Reglern für die Positionsregelung]
) <eval_pos_plots>

== Implementierung

Die Implementierung der Regler auf dem Zielsystem erfolgte mithilfe des Embedded Coders von MATLAB @EmbeddedCoder. Dabei erfolgt die Entwicklung der Regler vollständig in Simulink, wo die Algorithmen auch simulativ getestet und optimiert werden können. Für den Übergang von der Simulation zum realen System kann der Regler dann mit einem Klick in Quellcode überführt werden. Dieser lässt sich ohne Anpassungen in die bestehende Onboard-Software integrieren. Nach der anschließenden Kompilierung und Übertragung der gesamten Onboard-Software auf das Zielsystem ist der Regler einsatzbereit. Dies ermöglicht kurze Iterationszyklen zwischen Simulation und realem Test, da die zeitintensive und fehleranfällige manuelle Portierung der Algorithmen entfällt.

Ergänzend wurde untersucht, den Regler direkt auf dem Entwicklungsrechner auszuführen und die Mess- sowie Stellgrößen über eine Kabelverbindung zu kommunizieren. Dieser Ansatz hätte den Zwischenschritt der Neukompilierung der Onboard-Software eingespart. Allerdings konnte dabei die geforderte Regelrate von 200 Hz nicht erreicht werden, was primär auf die Latenzen innerhalb der Simulink-Umgebung zurückzuführen ist. Deshalb wurde letztlich die Implementierung auf dem Zielsystem beibehalten, um eine hohe Taktrate zu gewährleisten.
