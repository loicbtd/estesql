#ifndef ESTESQL_CREATE_DROP_TABLE_OR_DB_EXCEPTION_H
#define ESTESQL_CREATE_DROP_TABLE_OR_DB_EXCEPTION_H

#include "custom_exception.h"

class create_drop_table_or_db_exception : public custom_exception {

protected:
    const char *what() const throw() override {
        return "Error: CREATE and DROP should be followed by TABLE, DATABASE (or DB).";
    }
};


#endif //ESTESQL_CREATE_DROP_TABLE_OR_DB_EXCEPTION_H
