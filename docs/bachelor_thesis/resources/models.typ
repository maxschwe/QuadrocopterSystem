#import "@preview/cetz:0.4.2"

#let drone_model(plus_config) = {
  cetz.canvas({
  import cetz.draw: *

  set-style(
    mark: (fill: black, scale: 2),
    stroke: (thickness: 0.4pt, cap: "round"),
    angle: (
      radius: 0.3,
      label-radius: .22,
      fill: green.lighten(80%),
      stroke: (paint: green.darken(50%))
    ),
    content: (padding: 1pt)
  )

  let x_rot = 0deg
  let y_rot = 0deg
  let z_rot = 0deg

  if (not plus_config) {
    x_rot = 125.264deg
    y_rot = 0deg
    z_rot = 210deg
  } else {
    x_rot = 125.264deg
    y_rot = 0deg
    z_rot = 235deg
  }
  
  
  ortho(z: z_rot, y: y_rot, x: x_rot, sorted: false, {   
    let cylinder((x, y, z), radius, height, x_rot: x_rot, y_rot: y_rot, z_rot: z_rot, edge_included: (true, true)) = {
      let x1 = calc.cos(-z_rot) * radius
      let y1 = calc.sin(-z_rot) * radius
      let x2 = calc.cos(180deg - z_rot) * radius
      let y2 = calc.sin(180deg - z_rot) * radius
      
      circle((x, y, z), radius: radius, fill: white)

      merge-path(fill: white, {
        translate((x, y))
        if edge_included.at(0) {
          line((x1, y1, z), (x1, y1, z + height))
        }
        arc-through((x1, y1, z + height), (0, -radius, z + height), (x2, y2, z + height))
        if edge_included.at(1) {
          line((), (x2, y2, z))
        }
        arc-through((x2, y2, z), (0, -radius, z), (x1, y1, z))
        translate((-x, -y))
      })
    }

    let base_height = 0.5
    let base_radius = 1.34
    let rotor_radius = 0.2
    let arm_height = 0.3
    let arm_length = 3.0
    let arm_width = 0.25

    let arm_width_half = arm_width / 2
    let a1 = arm_length - calc.sqrt(1 - calc.pow(calc.sin(arm_width_half / rotor_radius), 2)) * rotor_radius
    let a2 = calc.sqrt(1 - calc.pow(calc.sin(arm_width_half / base_radius), 2)) * base_radius
    
    let b1 = -arm_width_half
    let b2 = arm_width_half

    let rotor_positions = ((arm_length, 0), (0, arm_length), (-arm_length, 0), (0, -arm_length))

    let numbering = (4, 3, 2, 1)

    for (i, (x_rotor, y_rotor)) in rotor_positions.enumerate() {
      translate((x_rotor, y_rotor))

      if calc.rem(i, 2) == 1 {
        arc((0.3, 0, 1), radius: 0.3, start: 0deg, delta: 300deg)
        mark((0.3, -.2, 1), -90deg, symbol: "stealth", scale: 1.2)
      } else {
        arc((0.3, 0, 1), radius: 0.3, start: 0deg, delta: -300deg)
        mark((0.3, .2, 1), 90deg, symbol: "stealth", scale: 1.2)
      }

      if plus_config {
        let n = numbering.at(i)
        if i == 1 or i == 2 {
          content((0.1, 0.8, 1.6), [$tau_(#n)$])
        } else {
          content((1.5, 0.2, 1.6), [$tau_(#n)$])
        }
      } else {
        content((-0.3, 0.3, 1.6), [$tau_#(i+1)$])
      }

      translate((-x_rotor, -y_rotor))
    }

    // arm 1
    cylinder((arm_length, 0, 0), rotor_radius, base_height)
    circle((arm_length, 0), radius: 0.1)
    line((a1, b1), (a2, b1), (a2, b1, arm_height), (a1, b1, arm_height), (a1, b1), fill: white)
    merge-path(fill: white, {
      line((a1, b2), (a2, b2))
      arc-through((), (base_radius, 0), (a2, b1))
      line((), (a1, b1))
      arc-through((), (arm_length - rotor_radius, 0), (a1, b2))
    })
    // arm 2
    cylinder((0, arm_length, 0), rotor_radius, base_height)
    circle((0, arm_length), radius: 0.1)
    line((b1, a1), (b1, a2), (b1, a2, arm_height), (b1, a1, arm_height), (b1, a1), fill: white)
    merge-path(fill: white, {
      line((b2, a1), (b2, a2))
      arc-through((), (0, base_radius), (b1, a2))
      line((), (b1, a1))
      arc-through((), (0, arm_length - rotor_radius), (b2, a1))
    })

    // Base
    cylinder((0, 0, 0), base_radius, base_height)

    // Arm 3
    cylinder((-arm_length, 0, 0), rotor_radius, base_height)
    circle((-arm_length, 0), radius: 0.1)
    line((-a1, b1), (-a2, b1), (-a2, b1, arm_height), (-a1, b1, arm_height), (-a1, b1), fill: white)
    merge-path(fill: white, {
      line((-a1, b2), (-a2, b2))
      arc-through((), (-base_radius, 0), (-a2, b1))
      line((), (-a1, b1))
      arc-through((), (- arm_length + rotor_radius, 0), (-a1, b2))
    })
    // Arm 4
    cylinder((0, -arm_length, 0), rotor_radius, base_height)
    circle((0, -arm_length), radius: 0.1)
    line((b1, -a1), (b1, -a2), (b1, -a2, arm_height), (b1, -a1, arm_height), (b1, -a1), fill: white)
    merge-path(fill: white, {
      line((b2, -a1), (b2, -a2))
      arc-through((), (0, -base_radius), (b1, -a2))
      line((), (b1, -a1))
      arc-through((), (0, - arm_length + rotor_radius), (b2, -a1))
    })


    for (i, (x_rotor, y_rotor)) in rotor_positions.enumerate() {
      translate((x_rotor, y_rotor))

      line((0, 0, -0.4), (0, 0, -1.5), mark: (end: "stealth"))
      if i == 0 or i == 3 {
        content((0.3, -0.30, -1.1), [$f_#numbering.at(i)$])
      } else {
        content((-0.3, 0.30, -1.1), [$f_#numbering.at(i)$])
      }
      for j in range(3) {
        merge-path(fill: white, {
          hobby((0, 0, 0), (0.2, 0.1), (1, 0))
          hobby((), (0.2, -0.1), (0, 0))
        })
        rotate(z: 120deg)
      }
      translate((-x_rotor, -y_rotor))
    }

    if (not plus_config) {
      rotate(z: 45deg)
    }

    circle((0, 0), radius: 0.05, fill: black)
    content((-0.3, -0.1), $K_"B"$, anchor: "west")
    line((0, 0, 0), (1, 0), mark: (end: "stealth"))
    content((), $x$, anchor: "east")
    line((0, 0), (0, -0.9), mark: (end: "stealth"))
    content((), $y$, anchor: "east")
    line((0, 0), (0, 0, -1.6), mark: (end: "stealth"))
    content((), $z$, anchor: "north")

    line((arm_length + 1.5, 0, 0), (arm_length + 3.0, 0, 0), mark: (end: "stealth"), stroke: (thickness: 3pt))
    content((arm_length + 2.9, -1.2, 0), [Vorwärts])

    if plus_config {
      translate((-5.0, 3.3, 0.5))
      circle((0, 0), radius: 0.05, fill: black)
      content((-0.5, -0.1), $K_"E"$, anchor: "west")
      line((0, 0, 0), (1.2, 0), mark: (end: "stealth"))
      content((), $x$, anchor: "east")
      line((0, 0), (0, -1), mark: (end: "stealth"))
      content((), $y$, anchor: "east")
      line((0, 0), (0, 0, -1.2), mark: (end: "stealth"))
      content((), $z$, anchor: "north")
      }
    })
})
}