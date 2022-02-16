#ifndef ESTESQL_INABILITY_TO_CREATE_DIRECTORY_EXCEPTION_H
#define ESTESQL_INABILITY_TO_CREATE_DIRECTORY_EXCEPTION_H

#include "custom_exception.h"

class inability_to_create_directory_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: inability to create directory";
    }
};

#endif //ESTESQL_INABILITY_TO_CREATE_DIRECTORY_EXCEPTION_H
