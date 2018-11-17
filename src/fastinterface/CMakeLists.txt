set(fastinterface_source
  computetables.cc
  fastinterface.cc
  convolutiontable.cc
  utilities.cc
  )

add_library(fastinterface OBJECT ${fastinterface_source})
