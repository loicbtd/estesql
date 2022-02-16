#ifndef ESTESQL_INDEX_FILE_H
#define ESTESQL_INDEX_FILE_H


#include <cstdint>
#include <filesystem>

#include "app/exceptions/file_is_not_open_exception.h"
#include "db_info.h"
#include "table_file.h"
#include "app/constants/file_extensions.h"

struct __attribute__((__packed__)) index_entry {
    bool is_active;
    uint32_t position;
    uint16_t length;
};

class index_file : public table_file {
private:
    static index_file* index_file_;

public:
    static index_file *get_instance();

    index_file() : table_file(INDEX_FILE_EXTENSION) {}

    void write_index_entry(const index_entry &entry, uint32_t offset);

    index_entry get_index_entry(uint32_t position);
};


#endif //ESTESQL_INDEX_FILE_H
