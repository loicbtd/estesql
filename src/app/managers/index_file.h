#ifndef ESTESQL_INDEX_FILE_H
#define ESTESQL_INDEX_FILE_H


#include <cstdint>
#include "table_file.h"

struct index_entry __attribute__((__packed__)) {
    bool is_active;
    uint32_t position ;
    uint16_t length;
};

class index_file : public table_file    {

public:
    void write_index_entry(const index_entry &entry, uint32_t offset);
    index_entry get_index_entry(uint32_t position);


};


#endif //ESTESQL_INDEX_FILE_H
