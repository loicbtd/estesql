#ifndef ESTESQL_CONTENT_FILE_H
#define ESTESQL_CONTENT_FILE_H


#include <vector>
#include "table_file.h"

class content_file : public table_file {

public:

    void write_record(const std::vector<uint8_t> &record, uint32_t offset);
    std::vector<uint8_t> read_record(uint16_t length, uint32_t offset);

};


#endif //ESTESQL_CONTENT_FILE_H
