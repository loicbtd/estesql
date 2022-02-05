#ifndef ESTESQL_FILE_IS_NOT_OPEN_EXCEPTION_H
#define ESTESQL_FILE_IS_NOT_OPEN_EXCEPTION_H

#include "custom_exception.h"

class file_is_not_open_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: file is not open";
    }
};

#endif //ESTESQL_FILE_IS_NOT_OPEN_EXCEPTION_H
