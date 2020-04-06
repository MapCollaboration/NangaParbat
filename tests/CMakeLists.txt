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

# build tests
add_executable(DrellYanCrossSection DrellYanCrossSection.cc)
target_link_libraries(DrellYanCrossSection NangaParbat)
add_test(DrellYanCrossSection DrellYanCrossSection)

# build tests
add_executable(TestChi2 TestChi2.cc)
target_link_libraries(TestChi2 NangaParbat)
add_test(TestChi2 TestChi2)

# build tests
add_executable(TestMinimisation TestMinimisation.cc)
target_link_libraries(TestMinimisation NangaParbat)
add_test(TestMinimisation TestMinimisation)

# build tests
add_executable(SIDISCrossSection SIDISCrossSection.cc)
target_link_libraries(SIDISCrossSection NangaParbat)
add_test(SIDISCrossSection SIDISCrossSection)

# build tests
add_executable(GridProduction GridProduction.cc)
target_link_libraries(GridProduction NangaParbat)
add_test(GridProduction GridProduction)
