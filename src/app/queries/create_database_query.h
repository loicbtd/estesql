#ifndef ESTESQL_CREATE_DATABASE_QUERY_H
#define ESTESQL_CREATE_DATABASE_QUERY_H

#include <filesystem>
#include <regex>

#include "database_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/constants/syntax_query.h"


namespace fs = std::filesystem;

class create_database_query : public database_related_query {

public:

    create_database_query();

    create_database_query(string sql) : database_related_query(sql) {}

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

    void createDb(string);

};


#endif //ESTESQL_CREATE_DATABASE_QUERY_H
