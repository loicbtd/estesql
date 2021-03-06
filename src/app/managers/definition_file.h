#ifndef ESTESQL_DEFINITION_FILE_H
#define ESTESQL_DEFINITION_FILE_H

#include <fstream>
#include <filesystem>

#include "app/constants/file_extensions.h"
#include "app/exceptions/file_is_not_open_exception.h"
#include "app/exceptions/inability_to_create_file_exception.h"
#include "app/helpers/db_table_utilities.h"
#include "app/enumerations/field_type_t.h"
#include "app/models/table_definition.h"
#include "table_file.h"
#include "db_info.h"


using namespace std;

class definition_file : public table_file {
private:
    static definition_file *definition_file_;

public:
    static definition_file *get_instance();

    definition_file() : table_file(DEFINITION_FILE_EXTENSION) {}

    table_definition get_table_definition();

    void write_table_definition(const table_definition &);

    vector<string> get_all_columns_names();

    vector<field_type_t> get_all_columns_types();

    uint16_t get_record_length();
};


#endif //ESTESQL_DEFINITION_FILE_H
