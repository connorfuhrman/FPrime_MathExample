cmake_minimum_required(VERSION 3.13)
#cmake_policy(SET CMP0048 NEW)
project(MathOpsExampleDeployment VERSION 1.0.0 LANGUAGES C CXX)


# Include F' core components
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")


# Add the components
set(COMP_SUBDIRS
  MathTypes
  MathPorts
  MathSender
  MathReceiver
  Top
)
foreach (subdir IN LISTS COMP_SUBDIRS)
  add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/${subdir}")
endforeach()

# Register the F' Topology
find_package(fmt REQUIRED)
set(SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/Top/Main.cpp")
set(MOD_DEPS
  ${PROJECT_NAME}/Top
  fmt::fmt)

register_fprime_deployment()

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)

# Set compile options
target_compile_options(${PROJECT_NAME} PUBLIC
  -Wall
  -Wextra
  -Werror
  -Wconversion
  -Wsign-conversion
  -Wformat-security
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Woverloaded-virtual
  -Wno-unused-parameter
  -Wundef)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
