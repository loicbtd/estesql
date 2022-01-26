#ifndef ESTESQL_QUERY_SIZE_EXCEPTION_H
#define ESTESQL_QUERY_SIZE_EXCEPTION_H

#include "custom_exception.h"

class query_size_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: query not long enough. size < 3.";
    }
};

#endif //ESTESQL_QUERY_SIZE_EXCEPTION_H
