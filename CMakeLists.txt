project(small)
cmake_minimum_required(VERSION 3.15)

set(LLVM_INSTALL_DIR "" CACHE PATH "LLVM intallation directory")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM REQUIRED CONFIG)
include_directories("${LLVM_INCLUDE_DIRS}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
set(LLVM_ENABLE_PLUGINS ON)
include(AddLLVM)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

if(NOT LLVM_ENABLE_RTTI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

if(WIN32 OR CYGWIN)
  set(LLVM_LINK_COMPONENTS Core Support)
endif()

# LLVM Passes
add_subdirectory("llvm/profiler")

