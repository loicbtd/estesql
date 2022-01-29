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
        src/app/managers/db_info.cpp src/app/managers/db_info.h src/app/managers/table_file.cpp src/app/managers/table_file.h src/app/models/table_definition.cpp src/app/models/table_definition.h src/app/enumerations/field_type_t.h src/app/managers/definition_file.cpp src/app/managers/definition_file.h src/app/managers/index_file.cpp src/app/managers/index_file.h src/app/managers/content_file.cpp src/app/managers/content_file.h src/app/managers/key_file.cpp src/app/managers/key_file.h src/app/enumerations/query_type.h src/app/queries/query_generator.cpp src/app/queries/query_generator.h src/app/constants/string_delimiters.h src/app/queries/create_database_query.cpp src/app/queries/create_database_query.h src/app/constants/string_key_words.h src/app/queries/use_query.cpp src/app/queries/use_query.h src/app/queries/database_related_query.cpp src/app/queries/database_related_query.h src/app/queries/table_related_query.cpp src/app/queries/table_related_query.h src/app/exceptions/query_size_exception.h src/app/exceptions/custom_exception.h src/app/exceptions/create_drop_table_or_db_exception.h src/app/exceptions/unknown_query_exception.h src/app/managers/db_utilities.cpp src/app/managers/db_utilities.h)

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})

# link libraries
#target_link_libraries(${PROJECT_NAME} ${SOME_LIB})
