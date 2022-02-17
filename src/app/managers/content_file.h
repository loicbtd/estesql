#ifndef ESTESQL_CONTENT_FILE_H
#define ESTESQL_CONTENT_FILE_H

#include <vector>
#include <cstring>

#include "table_file.h"
#include "index_file.h"

#include "app/constants/file_extensions.h"

class content_file : public table_file {
private:
    static content_file* content_file_;

public:
    static content_file *get_instance();

    content_file() : table_file(CONTENT_FILE_EXTENSION) {}

    void write_record(const vector<uint8_t> &record, uint32_t offset);

    vector<uint8_t> read_record(uint16_t length, uint32_t offset);
};

#endif //ESTESQL_CONTENT_FILE_H
