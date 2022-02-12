#ifndef ESTESQL_CONTENT_FILE_H
#define ESTESQL_CONTENT_FILE_H


#include <vector>
#include "table_file.h"

class content_file : public table_file {

public:
    void write_record(string record, uint32_t offset);

    vector<string> read_record(uint32_t offset);
};

#endif //ESTESQL_CONTENT_FILE_H
