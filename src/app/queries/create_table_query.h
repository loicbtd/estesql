#ifndef CREATE_TABLE_QUERY

#include "sql_query.h"

#define CREATE_TABLE_QUERY

using namespace std;

class create_table_query : public sql_query {
public:

    create_table_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;


};

#endif