# build exacutable
add_executable(CreateTables CreateTables.cc)
target_link_libraries(CreateTables NangaParbat)

add_executable(ComputeChi2 ComputeChi2.cc)
target_link_libraries(ComputeChi2 NangaParbat)

add_executable(RunFit RunFit.cc)
target_link_libraries(RunFit NangaParbat)

add_executable(Filter Filter.cc)
target_link_libraries(Filter NangaParbat)
