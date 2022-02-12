#ifndef ESTESQL_INSERT_DUPlICATE_COLUMNS_EXCEPTION_H
#define ESTESQL_INSERT_DUPlICATE_COLUMNS_EXCEPTION_H

#include "custom_exception.h"

class insert_duplicate_columns_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: The columns must be unique.";
    }
};

#endif //ESTESQL_INSERT_DUPlICATE_COLUMNS_EXCEPTION_H
