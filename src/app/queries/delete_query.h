#ifndef DELETE_QUERY
#define DELETE_QUERY

#include "table_related_query.h"

using namespace std;

class delete_query : public table_related_query {
public:

    delete_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif