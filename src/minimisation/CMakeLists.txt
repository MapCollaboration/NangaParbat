set(minimisation_source
  minimisation.cc
  fcnminuit.cc
  fcnceres.cc
  )

add_library(minimisation OBJECT ${minimisation_source})
