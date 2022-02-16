#ifndef ESTESQL_INABILITY_TO_CHECK_IF_FILE_EXISTS_EXCEPTION_H
#define ESTESQL_INABILITY_TO_CHECK_IF_FILE_EXISTS_EXCEPTION_H

#include "custom_exception.h"

class inability_to_check_if_file_exists_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: inability to check if file exists";
    }
};

#endif //ESTESQL_INABILITY_TO_CHECK_IF_FILE_EXISTS_EXCEPTION_H
