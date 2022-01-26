#ifndef UPDATE_QUERY

#include <iostream>
#include "sql_query.h"

#define UPDATE_QUERY

using namespace std;

class update_query : public sql_query {
public:

    update_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif