#import "titlepage.typ": titlepage
#import "declaration.typ": declaration

#import "@preview/subpar:0.2.2"
#import "@preview/cetz:0.4.2": canvas
#import "@preview/cetz-plot:0.1.3": plot

#let conf(
  type: none,
  title: none,
  author: none,
  submission_date: none,
  degree_program: none,
  chair: none,
  faculty: none,
  first_reviewer: none,
  second_reviewer: none,
  academic_supervisor: none,
  doc,
) = {
  show heading.where(level: 1): heading_title => [
    #pad(top: 3cm, bottom: 1.1cm)[
      #text(heading_title, size: 24pt)
    ]
  ]

  show heading.where(level: 1): it => {
    counter(figure.where(kind: image)).update(0)
    counter(figure.where(kind: table)).update(0)
    counter(math.equation).update(0)
    it
  }

  show heading.where(level: 2): heading_title => [
    #pad(top: 8mm, bottom: 4mm)[
      #text(heading_title, size: 18pt)
    ]
  ]

  show heading.where(level: 3): heading_title => [
    #pad(top: 4mm, bottom: 2mm)[
      #text(heading_title, size: 14pt)
    ]
  ]

  set text(size: 12pt, font: "New Computer Modern", lang: "de")
  set par(leading: 1em, spacing: 1.5em, justify: true, linebreaks: "simple")
  set math.vec(delim: ("[", "]"))
  set math.mat(column-gap: 0.8em, delim: ("[", "]"))

  titlepage(
    type: type,
    title: title,
    author: author,
    submission_date: submission_date,
    degree_program: degree_program,
    chair: chair,
    faculty: faculty,
    first_reviewer: first_reviewer,
    second_reviewer: second_reviewer,
    academic_supervisor: academic_supervisor,
  )

  set page(
    margin: (
      left: 36.8mm,
      top: 35mm,
      right: 19.8mm,
      bottom: 37mm,
    ),
  )

  counter(page).update(1)
  set page(
    numbering: "I",
    number-align: bottom + center,
  )

  include("short_summary.typ")
  pagebreak()

  counter(page).update(2)

  set page(
    numbering: "I",
    number-align: top + right,
    header: context {

      return [#h(1fr) #counter(page).display()]
      
    }
  )

  outline()


  set page(
    numbering: "I",
    number-align: top + right,
    header: context {
        let headings_after = query(
          heading.where(level: 1, outlined: true)
            .or(heading.where(level: 2))
              .or(heading.where(level: 3))
                .after(here())
        )
        
        if headings_after.len() > 0 and counter(page).at(headings_after.first().location()) == counter(page).get() and   headings_after.first().location().position().y.cm() == 3.5 {
          return [#h(1fr) #counter(page).display()]
        }
      
        let headings_before = query(
          heading.where(outlined: true)
            .or(heading.where(level: 2))
              .or(heading.where(level: 3))
                .before(here())
        )

        let heading_name

        if headings_before.len() == 0 {
          heading_name = "Inhaltsverzeichnis"
        } else {
          heading_name = [#counter(heading).display() #headings_before.last().body]
        }
        
        return underline([
          #set par(spacing: 1em)
          
          #heading_name
          #box(width: 1fr, repeat(" "))
          #counter(page).display()
          // #line(length: 100%, stroke: 0.5pt)
        ], offset: 5pt)
      }
  )

  set math.equation(numbering: it => {
    let count = counter(heading).get().first()
    numbering("(1.1)", count, it)
  })

  set figure(numbering: it => {
    let count = counter(heading).get().first()
    numbering("1.1", count, it)
  })

  show figure.where(kind: image): set figure(supplement: [Abb.])
  show figure.where(kind: table): set figure(supplement: [Tabelle])
  show figure.where(kind: table): it => {
    set figure.caption(separator: [: ], position: top)
    it
  }


  // pages with arabic numbering
  counter(page).update(1)
  set page(numbering: "1")
  set heading(numbering: "1.")

  // pages specified in main.typ
  doc

  pagebreak()

  set page(header: context{[#h(1fr) #counter(page).display()]})

  bibliography("../references.bib" , style: "ieee", title: "Literaturverzeichnis")

  pagebreak()

  outline(title: "Abbildungen", target: figure.where(kind: image))

  pagebreak()
  
  outline(title: "Tabellen", target: figure.where(kind: table))

  declaration(
    author: author,
    submission_date: submission_date,
  )
}

#let subfigures(
  columns: (auto, auto),
  ..args,  
) = {
  subpar.grid(
    columns: columns,
    supplement: [Abb.],
    numbering: it => {
      let count = counter(heading).get().first()
      numbering("1.1", count, it)
    },
    numbering-sub-ref: (parent, sub) => {
      let count = counter(heading).get().first()
      let p-str = numbering("1.1", count, parent)
      let s-str = numbering("a", sub)
      [#p-str#s-str]
    },
    ..args,
  )
}

// section headings, which are not shown in outline
#let runin(title) = [*#title* #linebreak()]

#let show_plot(
  file_configs, // Array of (path, indices) e.g., (("data1.csv", (([$phi_1$], 1),)), ("data2.csv", (([$phi_2$], 1),)))
  y_label, 
  size: (13, 6),
  y_limits: (-8, 14),
  raw_data: true
) = {
  let colors = (red, blue.lighten(20%), green, orange, purple)
  let strokes = ("dotted", "solid", "solid", "solid")
  let stroke_idx = 0

  return canvas({
    plot.plot(
      size: size,
      x-label: [Zeit ($s$)],
      y-label: y_label, 
      y-min: y_limits.at(0),
      y-max: y_limits.at(1),
      x-tick-step: 5,
      y-tick-step: 5,
      legend: "inner-north-west",
      {
        for (file_path, csv_indices) in file_configs {
          let raw-data = csv("../" + file_path)
          let header_less = raw-data.slice(1)
          if header_less.len() == 0 { continue }

          let t_offset = float(header_less.at(0).at(0))
          let deg_factor = 180 / calc.pi
          let time_factor = if raw_data { 1000 } else { 1 }

          // Process this specific file's series
          for (label_content, col_idx) in csv_indices {
            let data_points = header_less.map(row => {
              let r = row.map(float)
              let t = (r.at(0) - t_offset) / time_factor
              let val = r.at(col_idx)
              if raw_data { val *= deg_factor }
              (t, val)
            })

            plot.add(
              data_points,
              label: label_content,
              style: (
                stroke: (
                  paint: colors.at(calc.rem(stroke_idx, colors.len())), 
                  dash: strokes.at(calc.rem(stroke_idx, strokes.len())),
                  thickness: 1.5pt
                )
              )
            )
            stroke_idx += 1
          }
        }
      }
    )
  })
}

#let show_xy_plot(
  file_configs, // Array of (path: "...", series: ((label: [], x: 1, y: 2), ...))
  x_label: [X-Achse],
  y_label: [Y-Achse], 
  size: (12, 6),
  x_limits: (-0.7, 0.7),
  y_limits: (-0.5, 0.7),
  raw_data: true
) = {
  let colors = (red, blue.lighten(20%), green, orange, purple)
  let strokes = ("dotted", "solid", "solid", "solid")
  let stroke_idx = 0

  return canvas({
    plot.plot(
      size: size,
      x-label: x_label,
      y-label: y_label, 
      x-min: x_limits.at(0),
      x-max: x_limits.at(1),
      y-min: y_limits.at(0),
      y-max: y_limits.at(1),
      x-tick-step: 0.2,
      y-tick-step: 0.2,
      legend: "inner-north-west",
      {
        for config in file_configs {
          // Zugriff über Keys statt Indizes
          let file_path = config.path
          let series_list = config.series
          
          let raw_csv_data = csv("../" + file_path)
          let header_less = raw_csv_data.slice(1)
          if header_less.len() == 0 { continue }

          for s in series_list {
            let data_points = header_less.map(row => {
              // Zugriff auf x und y über die Namen im Dictionary
              let x_val = float(row.at(s.x))
              let y_val = float(row.at(s.y))
              
              (x_val, y_val)
            })

            plot.add(
              data_points,
              label: s.label,
              style: (
                stroke: (
                  paint: colors.at(calc.rem(stroke_idx, colors.len())), 
                  dash: strokes.at(calc.rem(stroke_idx, strokes.len())),
                  thickness: 1.5pt
                )
              )
            )
            stroke_idx += 1
          }
        }
      }
    )
  })
}