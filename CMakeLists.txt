cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

find_package(
  Boost 1.65 REQUIRED
  COMPONENTS
  system
)

add_executable( print
  src/expression.cpp
  src/print.cpp
  src/printer.cpp
)
target_link_libraries( print
  Boost::system
)
