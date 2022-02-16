#ifndef ESTESQL_BUILD_WHERE_CLAUSE_H
#define ESTESQL_BUILD_WHERE_CLAUSE_H

#include <string>
#include <regex>
#include <iostream>

#include "string_utilities.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/column_non_existing_exception.h"

#include "app/models/where_clause.h"

using namespace std;

class build_where_clause {

public:
    static where_clause
    build_where(const string &query, const string &syntaxe_exception, const vector<string> &columns_name_from_file);

};
#endif //ESTESQL_BUILD_WHERE_CLAUSE_H
