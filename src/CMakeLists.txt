add_subdirectory(fastinterface)
add_subdirectory(data)
add_subdirectory(chi2)

option(SHARED "Build shared-libray instead of static-libray" ON)
if(SHARED)
  add_library(NangaParbat SHARED $<TARGET_OBJECTS:fastinterface>
  $<TARGET_OBJECTS:data> $<TARGET_OBJECTS:chi2>)
else(SHARED)
  add_library(NangaParbat STATIC $<TARGET_OBJECTS:fastinterface>
  $<TARGET_OBJECTS:data> $<TARGET_OBJECTS:chi2>)
endif(SHARED)

target_link_libraries(NangaParbat ${YAML_LDFLAGS} ${APFELXX_LIBRARIES}
${LHAPDF_LIBRARIES} ${GSL_LIBRARIES})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/NangaParbat DESTINATION include)
install(TARGETS NangaParbat DESTINATION lib)
