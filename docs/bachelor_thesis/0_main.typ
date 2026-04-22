#import "conf/conf-unia-rt.typ": conf

// #show heading: set text(font: "Sans")

#show: conf.with(
  type: "Bachelorarbeit", // Bachelorarbeit or Seminararbeit
  title: "Entwurf und Evaluierung verschiedener Regelkonzepte \nfür einen Quadrocopter in der Lehre",
  author: "Maximilian Schweiger",
  submission_date: "23.03.2026",
  degree_program: "Ingenieurinformatik",
  chair: "Regelungstechnik",
  faculty: "Fakultät für Angewandte Informatik",
  first_reviewer: "Prof. Dr.-Ing. habil. Christoph Ament",
  second_reviewer: "Prof. Dr.-Ing. Lars Mikelsons",
  academic_supervisor: "M.Sc. Ferdinand Friedrich\nM.Sc. Johannes Wüstner",
)

#include("1_introduction.typ")
#pagebreak()
#include("2_system_description.typ")
#pagebreak()
#include("3_modeling.typ")
#pagebreak()
#include("4_controller_design.typ")
#pagebreak()
#include("5_fazit.typ")
