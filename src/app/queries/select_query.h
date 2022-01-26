#ifndef SELECT_QUERY
#define SELECT_QUERY

#include "table_related_query.h"

using namespace std;

class select_query : public table_related_query {
public:

    select_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif