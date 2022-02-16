#ifndef ESTESQL_INABILITY_TO_OPEN_FILE_EXCEPTION_H
#define ESTESQL_INABILITY_TO_OPEN_FILE_EXCEPTION_H

#include "custom_exception.h"

class inability_to_open_file_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: inability to open file";
    }
};

#endif //ESTESQL_INABILITY_TO_OPEN_FILE_EXCEPTION_H
