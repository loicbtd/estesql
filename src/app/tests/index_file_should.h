#ifndef ESTESQL_INDEX_FILE_SHOULD_H
#define ESTESQL_INDEX_FILE_SHOULD_H

#include <string>
#include <cstring>
#include <filesystem>
#include <map>
#include <iostream>
#include <ctime>

#include "test_base.h"
#include "app/constants/test_strings.h"
#include "app/managers/db_info.h"
#include "app/managers/index_file.h"
#include "app/models/table_definition.h"
#include "app/enumerations/field_type_t.h"

using namespace std;

class index_file_should: public test_base {
public:
    string name() override;
    map<string, bool> pass_tests() override;

private:
    bool write_and_retrieve_the_same();
};

#endif //ESTESQL_INDEX_FILE_SHOULD_H
