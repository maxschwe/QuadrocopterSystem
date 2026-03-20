#let titlepage(
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
) = {
  set align(center)

  v(0.6fr)

  image("Uni_Aug_Logo_Basis_pos_A.pdf", width: 30%)


  [
    #set text(size: 17pt)
    #set par(leading: 1.5em)
    #smallcaps("Universität Augsburg") \
    #faculty
  ]

  v(1fr)
  par(leading: 2.5em)[
    *#text(type, size: 17pt)* \
  ]
  [*#text(title, size: 14pt)*]
  v(1fr)

  let second_reviewer_row = if second_reviewer != none {
    ("2. Gutachter:", second_reviewer)
  } else {
    ()
  }

  table(
    columns: (auto, auto),
    align: (right, left),
    gutter: 0.75em,
    stroke: none,
    table.hline(stroke: 0.6pt),
    [], [],
    [vorgelegt von:], [#author],
    [eingereicht am:], [#submission_date],
    [Studiengang:], [#degree_program],
    [Anfertigung am Lehrstuhl:], [#chair],
    [], [#faculty],
    [1. Gutachter:], [#first_reviewer],
    ..for entry in second_reviewer_row {
      (entry,)
    },
    [Wissenschaftliche Betreuer:], [#academic_supervisor],
  )

  v(1fr)

  pagebreak()
}
