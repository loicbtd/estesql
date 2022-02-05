#ifndef ESTESQL_DEFINITION_FILE_H
#define ESTESQL_DEFINITION_FILE_H

#include <fstream>
#include <filesystem>
#include <iostream>

#include "app/exceptions/file_is_not_open_exception.h"
#include "app/exceptions/inability_to_create_file_exception.h"
#include "app/enumerations/field_type_t.h"
#include "app/models/table_definition.h"
#include "table_file.h"
#include "db_info.h"

using namespace std;

class definition_file : public table_file {

public:
    definition_file(string source_file) : table_file(source_file) {}

    table_definition get_table_definition();

    void write_table_definition(const table_definition &);

    bool exists() override;

    void open() override;

    void close() override;
};


#endif //ESTESQL_DEFINITION_FILE_H
