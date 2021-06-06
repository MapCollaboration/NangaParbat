cmake_minimum_required (VERSION 3.5)
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

if (NOT DEFINED CMAKE_MACOSX_RPATH)
   set(CMAKE_MACOSX_RPATH 0)
endif()

# the project name
project(NangaParbat)

# activating some global properties for the project
set(NangaParbat_VERSION 1.5.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# export version to file
configure_file(
  "${PROJECT_SOURCE_DIR}/inc/NangaParbat/version.h.in"
  "${PROJECT_SOURCE_DIR}/inc/NangaParbat/version.h"
)

find_package(PkgConfig REQUIRED)
pkg_search_module(YAML REQUIRED yaml-cpp)
#pkg_search_module(CERES ceres-solver)
find_package(Ceres QUIET)
if (NOT Ceres_FOUND)
  message ("CERES not found. Some parts of the code will not be compiled.")
endif ()
pkg_search_module(EIGEN3 eigen3)
pkg_search_module(GLOG libglog)
pkg_search_module(GFLAGS gflags)

# Configuration script
set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "${prefix}")
set(includedir "${prefix}/include")
set(libdir "${prefix}/lib")
configure_file(
  "${PROJECT_SOURCE_DIR}/bin/NangaParbat-config.in"
  "${PROJECT_SOURCE_DIR}/bin/NangaParbat-config"
)

include_directories(${PROJECT_SOURCE_DIR}/inc)

# LHAPDF
find_program(LHAPDF_CONFIG lhapdf-config REQUIRED)
if (LHAPDF_CONFIG)
  exec_program(${LHAPDF_CONFIG}
    ARGS --cflags
    OUTPUT_VARIABLE LHAPDF_CXX_FLAGS
  )
  set(LHAPDF_CXX_FLAGS ${LHAPDF_CXX_FLAGS} CACHE STRING INTERNAL)
  exec_program(${LHAPDF_CONFIG}
    ARGS --libs
    OUTPUT_VARIABLE LHAPDF_LIBRARIES
  )
  set(LHAPDF_LIBRARIES ${LHAPDF_LIBRARIES} CACHE STRING INTERNAL)
else(LHAPDF_CONFIG)
  message(FATAL_ERROR "LHAPDF not found!")
endif(LHAPDF_CONFIG)

# APFEL++
find_program(APFELXX_CONFIG apfelxx-config REQUIRED)
if (APFELXX_CONFIG)
  exec_program(${APFELXX_CONFIG}
    ARGS --cppflags
    OUTPUT_VARIABLE APFELXX_CXX_FLAGS
  )
  set(APFELXX_CXX_FLAGS ${APFELXX_CXX_FLAGS} CACHE STRING INTERNAL)
  exec_program(${APFELXX_CONFIG}
    ARGS --ldflags
    OUTPUT_VARIABLE APFELXX_LIBRARIES
  )
  set(APFELXX_LIBRARIES ${APFELXX_LIBRARIES} CACHE STRING INTERNAL)
else(APFELXX_CONFIG)
  message(FATAL_ERROR "APFEL++ not found!")
endif(APFELXX_CONFIG)

# GSL
find_program(GSL_CONFIG gsl-config)
if (GSL_CONFIG)
  exec_program(${GSL_CONFIG}
    ARGS --cflags
    OUTPUT_VARIABLE GSL_CXX_FLAGS
  )
  set(GSL_CXX_FLAGS ${GSL_CXX_FLAGS} CACHE STRING INTERNAL)
  exec_program(${GSL_CONFIG}
    ARGS --libs
    OUTPUT_VARIABLE GSL_LIBRARIES
  )
  set(GSL_LIBRARIES ${GSL_LIBRARIES} CACHE STRING INTERNAL)
else(GSL_CONFIG)
  message ("GSL not found. Some parts of the code will not be compiled.")
endif(GSL_CONFIG)

# ROOT
find_program(ROOT_CONFIG root-config)
if (ROOT_CONFIG)
  exec_program(${ROOT_CONFIG}
    ARGS --cflags
    OUTPUT_VARIABLE ROOT_CXX_FLAGS
  )
  set(ROOT_CXX_FLAGS ${ROOT_CXX_FLAGS} CACHE STRING INTERNAL)
  exec_program(${ROOT_CONFIG}
    ARGS --libs
    OUTPUT_VARIABLE ROOT_LIBRARIES
  )
  set(ROOT_LIBRARIES ${ROOT_LIBRARIES} CACHE STRING INTERNAL)

  # Include Minuit2 to the libraries of ROOT (not included by default)
  set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lMinuit2)
else(ROOT_CONFIG)
  message ("ROOT not found. Some parts of the code will not be compiled.")
endif(ROOT_CONFIG)

find_path(MINUIT2 Minuit2)
if (Minuit2)
  add_definitions(-DMINUIT2_NOT_BUNDLED_WITH_ROOT=true)
endif(Minuit2)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LHAPDF_CXX_FLAGS} ${APFELXX_CXX_FLAGS} ${GSL_CXX_FLAGS} ${YAML_CFLAGS} ${ROOT_CXX_FLAGS} ${EIGEN3_CFLAGS} ${Ceres_CFLAGS} ${GLOG_CFLAGS} ${GFLAGS_CFLAGS} -Wall -fPIC -Wunused")

# build target library
add_subdirectory(src)
add_subdirectory(run)

option(BUILD_TESTS "Build tests code" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(tools)
endif(BUILD_TESTS)

install(FILES ${PROJECT_SOURCE_DIR}/bin/NangaParbat-config
	   DESTINATION bin
	   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
