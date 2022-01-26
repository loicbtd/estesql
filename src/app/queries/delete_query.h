#ifndef DELETE_QUERY

#include <iostream>
#include "sql_query.h"

#define DELETE_QUERY

using namespace std;

class delete_query : public sql_query {
public:

    delete_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif