#ifndef ESTESQL_FILE_DOES_NOT_EXIST_EXCEPTION_H
#define ESTESQL_FILE_DOES_NOT_EXIST_EXCEPTION_H

#include "custom_exception.h"

class file_doest_not_exist_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: file does not exist";
    }
};

#endif //ESTESQL_FILE_DOES_NOT_EXIST_EXCEPTION_H
