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
    map<string, bool> passTests() override;

private:
    bool findIfADatabaseDirectoryExist();
};


#endif //ESTESQL_DB_UTILITIES_SHOULD_H
