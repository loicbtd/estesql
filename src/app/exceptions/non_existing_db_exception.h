#ifndef ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H
#define ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H

#include "custom_exception.h"

class non_existing_db_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: This database doesn't exist.";
    }
};

#endif //ESTESQL_ALREADY_EXISTING_TABLE_EXCEPTION_H
