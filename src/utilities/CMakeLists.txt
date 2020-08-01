set(utilities_source
  generategrid.cc
  listdir.cc
  bstar.cc
  direxists.cc
  numtostring.cc
  )

add_library(utilities OBJECT ${utilities_source})
