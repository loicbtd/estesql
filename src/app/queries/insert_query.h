#ifndef INSERT_QUERY
#define INSERT_QUERY


#include "table_related_query.h"

using namespace std;

class insert_query : public table_related_query {
public:

    insert_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif