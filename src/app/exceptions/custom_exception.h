#ifndef ESTESQL_CUSTOM_EXCEPTION_H
#define ESTESQL_CUSTOM_EXCEPTION_H

#include <exception>

class custom_exception : public std::exception {

public:
    virtual const char* what() const throw () = 0;
};



#endif //ESTESQL_CUSTOM_EXCEPTION_H
