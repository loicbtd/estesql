#ifndef DROP_TABLE_QUERY

#include <iostream>
#include "sql_query.h"

#define DROP_TABLE_QUERY

using namespace std;

class drop_table_query : public sql_query {
public:

    drop_table_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};

#endif