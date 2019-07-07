set(preprocessing_source
  PreprocessE288.cc
  PreprocessE605.cc
  PreprocessCDFRunI.cc
  PreprocessCDFRunII.cc
  PreprocessD0RunI.cc
  PreprocessD0RunII.cc
  PreprocessLHCb7TeV.cc
  PreprocessLHCb8TeV.cc
  PreprocessLHCb13TeV.cc
  PreprocessCMS7TeV.cc
  PreprocessCMS8TeV.cc
  PreprocessATLAS7TeV.cc
  PreprocessATLAS8TeV.cc
  )

add_library(preprocessing OBJECT ${preprocessing_source})
