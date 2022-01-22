#ifndef ESTESQL_KEY_FILE_H
#define ESTESQL_KEY_FILE_H


#include "table_file.h"

class key_file : public table_file {

public:
    
    uint64_t get_next_key();
    void update_key(uint64_t last_value);

};


#endif //ESTESQL_KEY_FILE_H
