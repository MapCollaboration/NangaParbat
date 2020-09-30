set(cuts_source
  cut.cc
  zcut.cc
  Trainingcut.cc
  cutfactory.cc
  )

add_library(cuts OBJECT ${cuts_source})
