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
add_executable(IntegrationTest IntegrationTest.cc)
target_link_libraries(IntegrationTest NangaParbat)
add_test(IntegrationTest IntegrationTest)
