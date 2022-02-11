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

    create_database_query(string sql) : database_related_query(sql) {

        smatch smatch_;
        string smatch_regex("create (database|db) [a-z0-9_-]+( )?");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(CREATE_DB_SYNTAX);
        }

        stringstream ss(sql);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vector_strings(begin, end);

        bool stop = false;
        for (auto & vector_string : vector_strings) {
            if (stop) {

                vector_string.erase(remove(vector_string.begin(), vector_string.end(), ';'), vector_string.end());
                setDbName(vector_string);
                break;

            }
            stop = vector_string=="database" || vector_string=="db";
        }

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

    void createDb(string);

};


#endif //ESTESQL_CREATE_DATABASE_QUERY_H
