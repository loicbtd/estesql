#ifndef ESTESQL_USE_QUERY_H
#define ESTESQL_USE_QUERY_H


#include "sql_query.h"

class use_query : public sql_query{
public:

    use_query(string sql) : sql_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};


#endif //ESTESQL_USE_QUERY_H
