#ifndef DROP_TABLE_QUERY
#define DROP_TABLE_QUERY

#include "table_related_query.h"

using namespace std;

class drop_table_query : public table_related_query {
public:

    drop_table_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};

#endif