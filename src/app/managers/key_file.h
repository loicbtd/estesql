#ifndef ESTESQL_KEY_FILE_H
#define ESTESQL_KEY_FILE_H

#include "table_file.h"
#include "app/constants/file_extensions.h"

class key_file : public table_file {
private:
    static key_file* key_file_;

public:
    static key_file *get_instance();

    key_file() : table_file(KEY_FILE_EXTENSION) {}

    uint64_t get_next_key();

    void update_key(uint64_t last_value);
};


#endif //ESTESQL_KEY_FILE_H
