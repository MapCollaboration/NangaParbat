# build exacutables
if (GSL_CONFIG AND ROOT_CONFIG AND Ceres_FOUND)
  add_executable(CreateTables CreateTables.cc)
  target_link_libraries(CreateTables NangaParbat)

  add_executable(RunFit RunFit.cc)
  target_link_libraries(RunFit NangaParbat)

  add_executable(ComputeMeanReplica ComputeMeanReplica.cc)
  target_link_libraries(ComputeMeanReplica NangaParbat)

  add_executable(Filter Filter.cc)
  target_link_libraries(Filter NangaParbat)

  add_executable(AvailableDataSets AvailableDataSets.cc)
  target_link_libraries(AvailableDataSets NangaParbat)

  add_executable(PlotTMDs PlotTMDs.cc)
  target_link_libraries(PlotTMDs NangaParbat)

  add_executable(AvailableParameterisations AvailableParameterisations.cc)
  target_link_libraries(AvailableParameterisations NangaParbat)

  add_executable(AvailableBstar AvailableBstar.cc)
  target_link_libraries(AvailableBstar NangaParbat)
endif()

add_executable(CreateGrids CreateGrids.cc)
target_link_libraries(CreateGrids NangaParbat)

add_executable(CreateStructGrids CreateStructGrids.cc)
target_link_libraries(CreateStructGrids NangaParbat)
