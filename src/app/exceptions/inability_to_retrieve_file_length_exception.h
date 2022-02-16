#ifndef ESTESQL_INABILITY_TO_RETRIEVE_FILE_LENGTH_EXCEPTION_H
#define ESTESQL_INABILITY_TO_RETRIEVE_FILE_LENGTH_EXCEPTION_H

#include "custom_exception.h"

class inability_to_retrieve_file_length_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: inability to retrieve file length";
    }
};

#endif //ESTESQL_INABILITY_TO_RETRIEVE_FILE_LENGTH_EXCEPTION_H
