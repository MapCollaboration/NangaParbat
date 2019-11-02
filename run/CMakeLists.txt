# build exacutable
add_executable(CreateTables CreateTables.cc)
target_link_libraries(CreateTables NangaParbat)

add_executable(RunFit RunFit.cc)
target_link_libraries(RunFit NangaParbat)

add_executable(Filter Filter.cc)
target_link_libraries(Filter NangaParbat)

add_executable(AvailableDataSets AvailableDataSets.cc)
target_link_libraries(AvailableDataSets NangaParbat)

add_executable(DirectPredictions DirectPredictions.cc)
target_link_libraries(DirectPredictions NangaParbat)

add_executable(PlotTMDs PlotTMDs.cc)
target_link_libraries(PlotTMDs NangaParbat)

add_executable(AvailableParameterisations AvailableParameterisations.cc)
target_link_libraries(AvailableParameterisations NangaParbat)

add_executable(AvailableBstar AvailableBstar.cc)
target_link_libraries(AvailableBstar NangaParbat)
