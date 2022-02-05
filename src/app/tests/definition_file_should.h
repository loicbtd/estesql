#ifndef ESTESQL_DEFINITION_FILE_SHOULD_H
#define ESTESQL_DEFINITION_FILE_SHOULD_H


#include <string>
#include <cstring>
#include <filesystem>
#include <map>
#include <iostream>
#include <ctime>

#include "test_base.h"
#include "app/constants/assets_paths.h"
#include "app/managers/db_info.h"
#include "app/managers/definition_file.h"
#include "app/models/table_definition.h"
#include "app/enumerations/field_type_t.h"


using namespace std;

class definition_file_should: public test_base {
public:
    string name() override;
    map<string, bool> pass_tests() override;

private:
    bool exist();
    bool not_exist();
    bool get_table_definition();
    bool write_get_table_definition();
};


#endif //ESTESQL_DEFINITION_FILE_SHOULD_H
