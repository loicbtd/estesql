#ifndef ESTESQL_MISSING_PRUMARY_KEY_EXCEPTION_H
#define ESTESQL_MISSING_PRUMARY_KEY_EXCEPTION_H

#include "custom_exception.h"

class missing_or_multiple_primary_key_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: You must have a PRIMARY_KEY column in your table";
    }
};

#endif //ESTESQL_MISSING_PRUMARY_KEY_EXCEPTION_H
