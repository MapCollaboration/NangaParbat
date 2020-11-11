set(cuts_source
  cut.cc
  zcut.cc
  qcut.cc
  Trainingcut.cc
  cutfactory.cc
  )

add_library(cuts OBJECT ${cuts_source})
