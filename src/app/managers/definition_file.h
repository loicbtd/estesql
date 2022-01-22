#ifndef ESTESQL_DEFINITION_FILE_H
#define ESTESQL_DEFINITION_FILE_H


#include "app/models/table_definition.h"
#include "table_file.h"

class definition_file : public table_file {

public:
    table_definition get_table_definition();
    void write_get_table_definition(const table_definition&);

};


#endif //ESTESQL_DEFINITION_FILE_H
