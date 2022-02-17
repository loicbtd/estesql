#ifndef ESTESQL_INVALID_UINT8_T_VECTOR_SIZE_EXCEPTION_H
#define ESTESQL_INVALID_UINT8_T_VECTOR_SIZE_EXCEPTION_H

#include "custom_exception.h"

class invalid_uint8_t_vector_size_exception : public custom_exception {
protected:
    const char *what() const throw() override {
        return "Error: invalid uint8_t vector size";
    }
};

#endif //ESTESQL_INVALID_UINT8_T_VECTOR_SIZE_EXCEPTION_H
