set(fastinterface_source
  fastinterface.cc
  convolutiontable.cc
  utilities.cc
  bstar.cc
  twobodyphasespace.cc
  )

add_library(fastinterface OBJECT ${fastinterface_source})
