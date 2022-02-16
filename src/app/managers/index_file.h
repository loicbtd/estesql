#ifndef ESTESQL_INDEX_FILE_H
#define ESTESQL_INDEX_FILE_H


#include <cstdint>
#include <filesystem>
#include <fstream>
#include <bitset>
#include <iostream>

#include "app/exceptions/file_is_not_open_exception.h"
#include "app/exceptions/index_file_is_not_valid_exception.h"
#include "app/exceptions/inability_to_read_undefined_index_file_position_exception.h"
#include "app/exceptions/inability_to_write_after_undefined_index_file_position_exception.h"
#include "db_info.h"
#include "table_file.h"
#include "app/constants/file_extensions.h"


#define INDEX_ENTRY_PERSISTED_SIZE_IN_BITS 56

#define INDEX_ENTRY_PERSISTED_IS_ACTIVE_SIZE_IN_BITS 8

#define INDEX_ENTRY_PERSISTED_POSITION_SIZE_IN_BITS 32

#define INDEX_ENTRY_PERSISTED_LENGTH_SIZE_IN_BITS 16

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

    int get_entries_count();
};


#endif //ESTESQL_INDEX_FILE_H
