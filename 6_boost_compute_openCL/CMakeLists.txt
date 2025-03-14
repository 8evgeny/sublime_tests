if(NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

# Generated by `boostdep --cmake compute`
# Copyright 2020, 2021 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.20)

project(boost_compute VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

add_library(boost_compute INTERFACE)
add_library(Boost::compute ALIAS boost_compute)

target_include_directories(boost_compute INTERFACE include)

target_link_libraries(boost_compute
  INTERFACE
    Boost::algorithm
    Boost::array
    Boost::assert
    Boost::atomic
    Boost::chrono
    Boost::config
    Boost::core
    Boost::filesystem
    Boost::function
    Boost::function_types
    Boost::fusion
    Boost::iterator
    Boost::lexical_cast
    Boost::mpl
    Boost::optional
    Boost::preprocessor
    Boost::property_tree
    Boost::proto
    Boost::range
    Boost::smart_ptr
    Boost::static_assert
    Boost::thread
    Boost::throw_exception
    Boost::tuple
    Boost::type_traits
    Boost::typeof
    Boost::utility
    Boost::uuid
)

else()

# ---------------------------------------------------------------------------
#  Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
#
#  Distributed under the Boost Software License, Version 1.0
#  See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
# ---------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)

project(BoostCompute)

set(CMAKE_MODULE_PATH ${BoostCompute_SOURCE_DIR}/cmake)
if (CMAKE_VERSION VERSION_LESS "3.1.0")
    list(APPEND CMAKE_MODULE_PATH "${BoostCompute_SOURCE_DIR}/cmake/opencl")
endif()

# find OpenCL
find_package(OpenCL REQUIRED)
include_directories(SYSTEM ${OpenCL_INCLUDE_DIRS})

# find Boost
find_package(Boost 1.54 REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# optional support for c++11
option(BOOST_COMPUTE_USE_CPP11 "Use C++11 features" OFF)
if(NOT MSVC)
  if(${BOOST_COMPUTE_USE_CPP11})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
endif()

# optional support for offline-caching
option(BOOST_COMPUTE_USE_OFFLINE_CACHE "Use offline cache for OpenCL program binaries" OFF)
if(${BOOST_COMPUTE_USE_OFFLINE_CACHE})
  add_definitions(-DBOOST_COMPUTE_USE_OFFLINE_CACHE)
endif()

# thread-safety options
option(BOOST_COMPUTE_THREAD_SAFE "Compile with BOOST_COMPUTE_THREAD_SAFE defined" OFF)
if(${BOOST_COMPUTE_THREAD_SAFE})
  add_definitions(-DBOOST_COMPUTE_THREAD_SAFE)
  if(${BOOST_COMPUTE_USE_CPP11})
    if(MSVC)
      if (MSVC_VERSION GREATER 1800)
        add_definitions(-DBOOST_COMPUTE_HAVE_THREAD_LOCAL)
      endif()
    else()
      add_definitions(-DBOOST_COMPUTE_HAVE_THREAD_LOCAL)
    endif()
  endif()
endif()

# optional third-party libraries
option(BOOST_COMPUTE_HAVE_EIGEN "Have Eigen" OFF)
option(BOOST_COMPUTE_HAVE_OPENCV "Have OpenCV" ON)
option(BOOST_COMPUTE_HAVE_QT "Have Qt" ON)
option(BOOST_COMPUTE_HAVE_VTK "Have VTK" OFF)
option(BOOST_COMPUTE_HAVE_CUDA "Have CUDA" OFF)
option(BOOST_COMPUTE_HAVE_TBB "Have TBB" OFF)
option(BOOST_COMPUTE_HAVE_BOLT "Have BOLT" OFF)

include_directories(include)

if(${OpenCL_HEADER_CL_EXT_FOUND})
  add_definitions(-DBOOST_COMPUTE_HAVE_HDR_CL_EXT)
endif()

# compiler options
option(BOOST_COMPUTE_ENABLE_COVERAGE "Enable code coverage generation" OFF)


option(BOOST_COMPUTE_BUILD_TESTS "Build the Boost.Compute tests" OFF)
if(${BOOST_COMPUTE_BUILD_TESTS})
  enable_testing()
  add_subdirectory(test)
endif()

option(BOOST_COMPUTE_BUILD_BENCHMARKS "Build the Boost.Compute benchmarks" OFF)
if(${BOOST_COMPUTE_BUILD_BENCHMARKS})
  add_subdirectory(perf)
endif()

option(BOOST_COMPUTE_BUILD_EXAMPLES "Build the Boost.Compute examples" ON)
if(${BOOST_COMPUTE_BUILD_EXAMPLES})
  add_subdirectory(example)
endif()

# configure cmake config file
configure_file(
  cmake/BoostComputeConfig.cmake.in
  ${BoostCompute_BINARY_DIR}/BoostComputeConfig.cmake
  @ONLY
)

# install cmake config file
install(
  FILES ${BoostCompute_BINARY_DIR}/BoostComputeConfig.cmake
  DESTINATION lib/cmake/BoostCompute
)

# install header files
install(DIRECTORY include/boost DESTINATION include/compute)

endif()
