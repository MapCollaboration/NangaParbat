add_subdirectory(fastinterface)
add_subdirectory(data)

option(SHARED "Build shared-libray instead of static-libray" ON)
if(SHARED)
  add_library(NangaParbat SHARED $<TARGET_OBJECTS:fastinterface> $<TARGET_OBJECTS:data>)
else(SHARED)
  add_library(NangaParbat STATIC $<TARGET_OBJECTS:fastinterface> $<TARGET_OBJECTS:data>)
endif(SHARED)

target_link_libraries(NangaParbat ${YAML_LDFLAGS} ${APFELXX_LIBRARIES} ${LHAPDF_LIBRARIES})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc/NangaParbat DESTINATION include)
install(TARGETS NangaParbat DESTINATION lib)
