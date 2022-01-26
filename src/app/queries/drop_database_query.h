#ifndef DROP_DATABASE_QUERY

#include "database_related_query.h"

#define DROP_DATABASE_QUERY

using namespace std;

class drop_database_query : public database_related_query {
public:

    drop_database_query(string sql) : database_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif