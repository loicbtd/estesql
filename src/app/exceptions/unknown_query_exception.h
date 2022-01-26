#ifndef ESTESQL_UNKNOWN_QUERY_EXCEPTION_H
#define ESTESQL_UNKNOWN_QUERY_EXCEPTION_H

#include "custom_exception.h"

class unknown_query_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: Unknown query. Queries available are : CREATE, SELECT, INSERT, UPDATE, DELETE, DROP and USE.";
    }
};


#endif //ESTESQL_UNKNOWN_QUERY_EXCEPTION_H
