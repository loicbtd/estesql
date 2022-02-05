#ifndef ESTESQL_SQL_INVALID_SYNTAX_EXCEPTION_H
#define ESTESQL_SQL_INVALID_SYNTAX_EXCEPTION_H

#include <string>

#include "custom_exception.h"

class slq_invalid_syntax_exception : public custom_exception {

public:
    slq_invalid_syntax_exception(const std::string error): msg(error){}

protected:
    const char *what() const throw() override {
        return msg.c_str();
    }

    std::string msg;

};



#endif //ESTESQL_SQL_INVALID_SYNTAX_EXCEPTION_H
