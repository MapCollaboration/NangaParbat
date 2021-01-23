set(utilities_source
  generategrid.cc
  linearsystems.cc
  listdir.cc
  bstar.cc
  direxists.cc
  numtostring.cc
  tostringwprecision.cc
  )

add_library(utilities OBJECT ${utilities_source})
