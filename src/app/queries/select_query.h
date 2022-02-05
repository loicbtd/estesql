#ifndef SELECT_QUERY
#define SELECT_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/constants/syntax_query.h"

using namespace std;

class select_query : public table_related_query {
public:

    select_query(string sql) : table_related_query(sql) {
        //TODO check if " from [a-z_-] " then vectorize sql, setTableName with the word after "from"
    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif