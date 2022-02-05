#include "db_utilities_should.h"

string db_utilities_should::name() {
    return "db_utilities";
}

map<string, bool> db_utilities_should::passTests() {
    map<string, bool> results;

    results.insert(pair("findIfADatabaseDirectoryExist", findIfADatabaseDirectoryExist()));

    return results;
}

bool db_utilities_should::findIfADatabaseDirectoryExist() {
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

