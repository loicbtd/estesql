#ifndef ESTESQL_COLUMN_NON_EXISTING_EXCEPTION_H
#define ESTESQL_COLUMN_NON_EXISTING_EXCEPTION_H

#include "custom_exception.h"

class column_non_existing_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: At least one column doesn't exists in the query.";
    }
};

#endif //ESTESQL_COLUMN_NON_EXISTING_EXCEPTION_H
