#ifndef ESTESQL_QUERY_SINGLETON_H
#define ESTESQL_QUERY_SINGLETON_H

#include <string>
#include <sstream>
#include <memory>
#include "sql_query.h"

#include "app/enumerations/query_type.h"
#include "app/constants/string_delimiters.h"

using namespace std;

class query_singleton {


protected:
    query_singleton() {}

    static query_singleton* singleton_;

public:

    query_singleton(query_singleton &other) = delete;

    void operator=(const query_singleton &) = delete;

    static query_singleton *GetInstance();

    unique_ptr<sql_query> query_generator(string);

    static bool test(const string&);

};


#endif //ESTESQL_QUERY_SINGLETON_H
