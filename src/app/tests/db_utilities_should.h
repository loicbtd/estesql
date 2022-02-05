#ifndef ESTESQL_DB_UTILITIES_SHOULD_H
#define ESTESQL_DB_UTILITIES_SHOULD_H

#include <iostream>
#include <string>
#include <filesystem>

#include "test_base.h"
#include <map>


using namespace std;

class db_utilities_should: public test_base {
public:
    string name() override;
    map<string, bool> pass_tests() override;

private:
    bool find_if_a_database_directory_exists();
};

#endif //ESTESQL_DB_UTILITIES_SHOULD_H
