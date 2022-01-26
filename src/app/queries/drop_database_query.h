#ifndef DROP_DATABASE_QUERY

#include <iostream>
#include "sql_query.h"

#define DROP_DATABASE_QUERY

using namespace std;

class drop_database_query : public sql_query {
public:

    drop_database_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif