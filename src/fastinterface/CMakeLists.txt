set(fastinterface_source
  fastinterface.cc
  convolutiontable.cc
  utilities.cc
  twobodyphasespace.cc
  twoparticlephasespace.cc
  )

add_library(fastinterface OBJECT ${fastinterface_source})
