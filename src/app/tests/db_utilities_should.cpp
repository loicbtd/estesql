#include "db_utilities_should.h"

string db_utilities_should::name() {
    return "db_utilities_sould";
}

map<string, bool> db_utilities_should::pass_tests() {
    map<string, bool> results;

    results.insert(pair("find_if_a_database_directory_exists", find_if_a_database_directory_exists()));

    return results;
}

bool db_utilities_should::find_if_a_database_directory_exists() {
    // Arrange
    try {
        filesystem::create_directories("tmp/persistence_test");
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    // Act

    // Assert

    return false;
}

