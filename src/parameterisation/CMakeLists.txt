set(parameterisation_source
  parameterisation.cc
  meanreplica.cc
 nonpertfunctions.cc
  )

add_library(parameterisation OBJECT ${parameterisation_source})
