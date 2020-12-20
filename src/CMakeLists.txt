if (GSL_CONFIG)
  add_subdirectory(fastinterface)
  set(TOBJ ${TOBJ} $<TARGET_OBJECTS:fastinterface>)
  add_subdirectory(data)
  set(TOBJ ${TOBJ} $<TARGET_OBJECTS:data>)
  add_subdirectory(preprocessing)
  set(TOBJ ${TOBJ} $<TARGET_OBJECTS:preprocessing>)
  add_subdirectory(chi2)
  set(TOBJ ${TOBJ} $<TARGET_OBJECTS:chi2>)
endif ()

if (GSL_CONFIG AND ROOT_CONFIG AND Ceres_FOUND)
  add_subdirectory(minimisation)
  set(TOBJ ${TOBJ} $<TARGET_OBJECTS:minimisation>)
endif ()

add_subdirectory(parameterisation)
set(TOBJ ${TOBJ} $<TARGET_OBJECTS:parameterisation>)

add_subdirectory(tmdgrid)
set(TOBJ ${TOBJ} $<TARGET_OBJECTS:tmdgrid>)

add_subdirectory(utilities)
set(TOBJ ${TOBJ} $<TARGET_OBJECTS:utilities>)

option(SHARED "Build shared-libray instead of static-libray" ON)
if(SHARED)
  add_library(NangaParbat SHARED ${TOBJ})
else(SHARED)
  add_library(NangaParbat STATIC ${TOBJ})
endif(SHARED)

target_link_libraries(NangaParbat ${YAML_LDFLAGS} ${APFELXX_LIBRARIES} ${ROOT_LIBRARIES}
${LHAPDF_LIBRARIES} ${GSL_LIBRARIES} ${EIGEN3_LDFLAGS}
${CERES_LIBRARIES} ${GLOG_LDFLAGS} ${GFLAGS_LDFLAGS})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/NangaParbat DESTINATION include)
install(TARGETS NangaParbat DESTINATION lib)
