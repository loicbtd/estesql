#ifndef ESTESQL_USE_QUERY_H
#define ESTESQL_USE_QUERY_H


#include "database_related_query.h"

class use_query : public database_related_query {
public:

    use_query(string sql) : database_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};


#endif //ESTESQL_USE_QUERY_H
