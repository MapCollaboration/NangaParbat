# build tests
add_executable(BenchmarkNangaParbat BenchmarkNangaParbat.cc)
target_link_libraries(BenchmarkNangaParbat NangaParbat)
add_test(BenchmarkNangaParbat BenchmarkNangaParbat)

# build tests
add_executable(EvolutionMatching EvolutionMatching.cc)
target_link_libraries(EvolutionMatching NangaParbat)
add_test(EvolutionMatching EvolutionMatching)

# build tests
add_executable(qTintegration qTintegration.cc)
target_link_libraries(qTintegration NangaParbat)
add_test(qTintegration qTintegration)

# build tests
add_executable(TableTest TableTest.cc)
target_link_libraries(TableTest NangaParbat)
add_test(TableTest TableTest)
