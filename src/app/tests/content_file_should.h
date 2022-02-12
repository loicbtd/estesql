#ifndef ESTESQL_CONTENT_FILE_SHOULD_H
#define ESTESQL_CONTENT_FILE_SHOULD_H


#include <string>
#include <cstring>
#include <filesystem>
#include <map>
#include <iostream>
#include <ctime>

#include "test_base.h"
#include "app/constants/test_strings.h"
#include "app/managers/db_info.h"
#include "app/managers/definition_file.h"
#include "app/models/table_definition.h"
#include "app/enumerations/field_type_t.h"


using namespace std;

class content_file_should: public test_base {
public:
    string name() override;
    map<string, bool> pass_tests() override;
};


#endif //ESTESQL_CONTENT_FILE_SHOULD_H
