#ifndef ESTESQL_INABILITY_TO_WRITE_AFTER_UNDEFINED_INDEX_FILE_POSITION_EXCEPTION_H
#define ESTESQL_INABILITY_TO_WRITE_AFTER_UNDEFINED_INDEX_FILE_POSITION_EXCEPTION_H

#include "custom_exception.h"

class inability_to_write_after_undefined_index_file_position_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: inability to write after undefined index file position";
    }
};

#endif //ESTESQL_INABILITY_TO_WRITE_AFTER_UNDEFINED_INDEX_FILE_POSITION_EXCEPTION_H
