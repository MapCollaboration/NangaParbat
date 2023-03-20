set(cuts_source
  cut.cc
  zcut.cc
  xcut.cc
  qcut.cc
  xzcut.cc
  Trainingcut.cc
  cutfactory.cc
  )

add_library(cuts OBJECT ${cuts_source})
