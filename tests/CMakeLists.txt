# build tests
if (GSL_CONFIG AND ROOT_CONFIG AND Ceres_FOUND)
  add_executable(BenchmarkNangaParbat BenchmarkNangaParbat.cc)
  target_link_libraries(BenchmarkNangaParbat NangaParbat)
  add_test(BenchmarkNangaParbat BenchmarkNangaParbat)

  add_executable(EvolutionMatching EvolutionMatching.cc)
  target_link_libraries(EvolutionMatching NangaParbat)
  add_test(EvolutionMatching EvolutionMatching)

  add_executable(qTintegration qTintegration.cc)
  target_link_libraries(qTintegration NangaParbat)
  add_test(qTintegration qTintegration)

  add_executable(IntegrationTest IntegrationTest.cc)
  target_link_libraries(IntegrationTest NangaParbat)
  add_test(IntegrationTest IntegrationTest)

  add_executable(DrellYanCrossSection DrellYanCrossSection.cc)
  target_link_libraries(DrellYanCrossSection NangaParbat)
  add_test(DrellYanCrossSection DrellYanCrossSection)

  add_executable(TestChi2 TestChi2.cc)
  target_link_libraries(TestChi2 NangaParbat)
  add_test(TestChi2 TestChi2)

  add_executable(TestMinimisation TestMinimisation.cc)
  target_link_libraries(TestMinimisation NangaParbat)
  add_test(TestMinimisation TestMinimisation)

  add_executable(SIDISCrossSection SIDISCrossSection.cc)
  target_link_libraries(SIDISCrossSection NangaParbat)
  add_test(SIDISCrossSection SIDISCrossSection)
endif ()

add_executable(GridProduction GridProduction.cc)
target_link_libraries(GridProduction NangaParbat)
add_test(GridProduction GridProduction)

add_executable(TestConvolution TestConvolution.cc)
target_link_libraries(TestConvolution NangaParbat)
add_test(TestConvolution TestConvolution)

add_executable(FUUTGridProduction FUUTGridProduction.cc)
target_link_libraries(FUUTGridProduction NangaParbat)
add_test(FUUTGridProduction FUUTGridProduction)