#ifndef ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H
#define ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H

#include "custom_exception.h"

class already_existing_table_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: Table already existing.";
    }
};

#endif //ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H
