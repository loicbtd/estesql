#ifndef ESTESQL_TABLE_RELATED_QUERY_H
#define ESTESQL_TABLE_RELATED_QUERY_H


#include "sql_query.h"

class table_related_query : public sql_query {

public:
    table_related_query(string sql): sql_query(sql) {}

    const string &get_table_name() const;

    void set_table_name(const string &tableName);


protected:
    virtual void parse() override = 0;

    virtual void check() override = 0;

    virtual void expand() override = 0;

    virtual void execute() override= 0 ;

private:
    string table_name;

};


#endif //ESTESQL_TABLE_RELATED_QUERY_H
