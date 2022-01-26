#ifndef SELECT_QUERY

#include <iostream>
#include "sql_query.h"

#define SELECT_QUERY

using namespace std;

class select_query : public sql_query {
public:

    select_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif