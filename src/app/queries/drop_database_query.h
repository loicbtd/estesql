#ifndef DROP_DATABASE_QUERY
#define DROP_DATABASE_QUERY

#include <regex>

#include "database_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/constants/syntax_query.h"

using namespace std;

class drop_database_query : public database_related_query {
public:

    drop_database_query(string sql) : database_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif