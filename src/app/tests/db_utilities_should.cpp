#include "db_utilities_should.h"

string db_utilities_should::name() {
    return "db_utilities_sould";
}

map<string, bool> db_utilities_should::pass_tests() {
    return {
            {"find_if_a_database_directory_exists", find_if_a_database_directory_exists()},
    };
}

bool db_utilities_should::find_if_a_database_directory_exists() {
    // Arrange
    try {
        filesystem::create_directories(DATABASE1_PATH);
    } catch (exception &) {
        return false;
    }

    // Act
    bool exists;
    try {
        exists = db_utilities::exists(DATABASE1_PATH);
    } catch (exception &){
        return false;
    }

    // Assert
    return exists;
}

