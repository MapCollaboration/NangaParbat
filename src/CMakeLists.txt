add_subdirectory(fastinterface)

option(SHARED "Build shared-libray instead of static-libray" ON)
if(SHARED)
  add_library(NangaParbat SHARED $<TARGET_OBJECTS:fastinterface>)
else(SHARED)
  add_library(NangaParbat STATIC $<TARGET_OBJECTS:fastinterface>)
endif(SHARED)

target_link_libraries(NangaParbat ${YAML_LDFLAGS} ${APFELXX_LIBRARIES} ${LHAPDF_LIBRARIES})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/NangaParbat DESTINATION include)
install(TARGETS NangaParbat DESTINATION lib)
