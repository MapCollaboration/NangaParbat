add_subdirectory(fastinterface)
add_subdirectory(data)
add_subdirectory(chi2)
add_subdirectory(minimisation)
add_subdirectory(parameterisation)
add_subdirectory(preprocessing)

option(SHARED "Build shared-libray instead of static-libray" ON)
if(SHARED)
  add_library(NangaParbat SHARED $<TARGET_OBJECTS:fastinterface>
  $<TARGET_OBJECTS:data> $<TARGET_OBJECTS:chi2>
  $<TARGET_OBJECTS:minimisation> $<TARGET_OBJECTS:parameterisation> $<TARGET_OBJECTS:preprocessing>)
else(SHARED)
  add_library(NangaParbat STATIC $<TARGET_OBJECTS:fastinterface>
  $<TARGET_OBJECTS:data> $<TARGET_OBJECTS:chi2>
  $<TARGET_OBJECTS:minimisation> $<TARGET_OBJECTS:parameterisation> $<TARGET_OBJECTS:preprocessing>)
endif(SHARED)

target_link_libraries(NangaParbat ${YAML_LDFLAGS} ${APFELXX_LIBRARIES} ${ROOT_LIBRARIES}
${LHAPDF_LIBRARIES} ${GSL_LIBRARIES} ${EIGEN3_LDFLAGS}
${CERES_LDFLAGS} ${GLOG_LDFLAGS} ${GFLAGS_LDFLAGS})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/NangaParbat DESTINATION include)
install(TARGETS NangaParbat DESTINATION lib)
