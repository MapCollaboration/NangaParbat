set(preprocessing_source
  preprocessE288.cc
  preprocessE605.cc
  preprocessCDFRunI.cc
  preprocessCDFRunII.cc
  preprocessD0RunI.cc
  preprocessD0RunII.cc
  preprocessD0RunIImu.cc
  preprocessPHENIX200.cc
  preprocessSTAR510.cc
  preprocessLHCb7TeV.cc
  preprocessLHCb8TeV.cc
  preprocessLHCb13TeV.cc
  preprocessCMS7TeV.cc
  preprocessCMS8TeV.cc 
  preprocessCMS13TeV.cc
  preprocessATLAS7TeV.cc
  preprocessATLAS8TeV.cc
  preprocessEICPseudodata.cc
  preprocessCOMPASS.cc
  preprocessHERMES.cc
  preprocessE537.cc
  preprocessE537_xF.cc
  preprocessE615.cc
  preprocessE615_xF.cc
  )

add_library(preprocessing OBJECT ${preprocessing_source})
