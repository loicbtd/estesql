cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(estesql)

include_directories(
  src
)

file(GLOB_RECURSE HEADER "src/**/*.h")
file(GLOB_RECURSE SOURCE "src/**/*.cpp")

add_executable(${PROJECT_NAME}
  src/main.cpp
  ${SOURCE}
  ${HEADER}
)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})