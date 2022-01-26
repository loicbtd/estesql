#ifndef UPDATE_QUERY
#define UPDATE_QUERY

#include "table_related_query.h"

using namespace std;

class update_query : public table_related_query {
public:

    update_query(string sql) : table_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif