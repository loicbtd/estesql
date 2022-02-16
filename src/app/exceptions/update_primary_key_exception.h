#ifndef ESTESQL_UPDATE_PRIMARY_KEY_EXCEPTION_H
#define ESTESQL_UPDATE_PRIMARY_KEY_EXCEPTION_H

#include "custom_exception.h"

class update_primary_key_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: You can't update a primary_key.";
    }
};

#endif //ESTESQL_UPDATE_PRIMARY_KEY_EXCEPTION_H
