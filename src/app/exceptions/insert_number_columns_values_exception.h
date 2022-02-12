#ifndef ESTESQL_INSERT_NUMBER_COLUMNS_VALUES_EXCEPTION_H
#define ESTESQL_INSERT_NUMBER_COLUMNS_VALUES_EXCEPTION_H

#include "custom_exception.h"

class insert_number_columns_values_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: Number of columns must be equal to the number of values.";
    }
};

#endif //ESTESQL_INSERT_NUMBER_COLUMNS_VALUES_EXCEPTION_H
