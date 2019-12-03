set(utilities_source
  generategrid.cc
  linearsystems.cc
  listdir.cc
  bstar.cc
  )

add_library(utilities OBJECT ${utilities_source})
