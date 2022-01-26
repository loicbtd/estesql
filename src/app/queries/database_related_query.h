#ifndef ESTESQL_DATABASE_RELATED_QUERY_H
#define ESTESQL_DATABASE_RELATED_QUERY_H


#include "sql_query.h"

class database_related_query : public sql_query {

public:
    database_related_query(string sql): sql_query(sql) {}

    const string &getDbName() const;

    void setDbName(const string &dbName);

protected:
    virtual void parse() override = 0;

    virtual void check() override = 0;

    virtual void expand() override = 0;

    virtual void execute() override= 0 ;

private:
    string db_name;

};


#endif //ESTESQL_DATABASE_RELATED_QUERY_H
