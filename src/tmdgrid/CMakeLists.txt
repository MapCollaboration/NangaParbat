set(tmdgrid_source
  createtmdgrid.cc
  tmdgrid.cc
  factories.cc
  structgrid.cc
  createstructgrid.cc
  )

add_library(tmdgrid OBJECT ${tmdgrid_source})
