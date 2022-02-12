#ifndef ESTESQL_WRONG_TYPE_EXCEPTION_H
#define ESTESQL_WRONG_TYPE_EXCEPTION_H

#include "custom_exception.h"

class wrong_type_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: The enterred value doesn't match the column type.";
    }
};



#endif //ESTESQL_WRONG_TYPE_EXCEPTION_H
