#ifndef INSERT_QUERY

#include <iostream>
#include "sql_query.h"

#define INSERT_QUERY

using namespace std;

class insert_query : public sql_query {
public:

    insert_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif