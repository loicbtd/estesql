#ifndef ESTESQL_CREATE_DATABASE_QUERY_H
#define ESTESQL_CREATE_DATABASE_QUERY_H


#include "database_related_query.h"

class create_database_query : public database_related_query {

public:

    create_database_query(string sql) : database_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};


#endif //ESTESQL_CREATE_DATABASE_QUERY_H
