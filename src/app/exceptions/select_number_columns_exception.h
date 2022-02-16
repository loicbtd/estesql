#ifndef ESTESQL_SELECT_NUMBER_COLUMNS_EXCEPTION_H
#define ESTESQL_SELECT_NUMBER_COLUMNS_EXCEPTION_H

#include "custom_exception.h"

class select_number_columns_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: Too many column in select query.";
    }
};

#endif //ESTESQL_SELECT_NUMBER_COLUMNS_EXCEPTION_H
