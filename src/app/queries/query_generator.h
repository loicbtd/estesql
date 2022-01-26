#ifndef ESTESQL_QUERY_GENERATOR_H
#define ESTESQL_QUERY_GENERATOR_H

#include <string>
#include <sstream>
#include <memory>
#include "sql_query.h"

#include "app/enumerations/query_type.h"
#include "app/constants/string_delimiters.h"

using namespace std;

class query_generator {


protected:
    query_generator() {}

public:
    static unique_ptr<sql_query> generate_query(const string&);

};


#endif //ESTESQL_QUERY_GENERATOR_H
