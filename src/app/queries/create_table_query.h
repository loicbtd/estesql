#ifndef CREATE_TABLE_QUERY
#define CREATE_TABLE_QUERY

#include "table_related_query.h"

using namespace std;

class create_table_query : public table_related_query {
public:

    create_table_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;


};

#endif