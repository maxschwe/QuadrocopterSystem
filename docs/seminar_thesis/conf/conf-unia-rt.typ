#import "titlepage.typ": titlepage
#import "declaration.typ": declaration

#import "@preview/subpar:0.2.2"

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

        return underline([
          #set par(spacing: 1em)
          #counter(heading).display()
          #headings_before.last().body
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

  outline()

  // pages with arabic numbering
  counter(page).update(0)
  set page(numbering: "1")
  set heading(numbering: "1.")

  // pages specified in main.typ
  doc

  pagebreak()

  set page(header: context{[#h(1fr) #counter(page).display()]})

  bibliography("../references.bib" , style: "ieee")

  pagebreak()

  outline(title: "Abbildungen", target: figure)

  declaration(
    author: author,
    submission_date: submission_date,
  )
}

#let subfigures(
  ..args,  
) = {
  subpar.grid(
    columns: (auto, auto),
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
