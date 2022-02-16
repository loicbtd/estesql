#ifndef ESTESQL_INDEX_FILE_IS_NOT_VALID_EXCEPTION_H
#define ESTESQL_INDEX_FILE_IS_NOT_VALID_EXCEPTION_H

#include "custom_exception.h"

class index_file_is_not_valid_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: index file is not valid";
    }
};

#endif //ESTESQL_INDEX_FILE_IS_NOT_VALID_EXCEPTION_H
