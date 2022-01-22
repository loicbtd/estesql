cmake_minimum_required(VERSION 3.0)

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

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})

# link libraries
#target_link_libraries(${PROJECT_NAME} ${SOME_LIB})