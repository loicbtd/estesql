#ifndef ESTESQL_USE_QUERY_H
#define ESTESQL_USE_QUERY_H

#include <filesystem>
#include <regex>

#include "database_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/already_existing_db_exception.h"
#include "app/exceptions/non_existing_db_exception.h"

#include "app/constants/syntax_query.h"

#include "app/managers/db_info.h"

#include "app/helpers/db_table_utilities.h"
#include "app/helpers/file_set_up.h"


class use_query : public database_related_query {
public:

    use_query(string sql) : database_related_query(sql) {
        smatch smatch_;
        string smatch_regex("use [a-z0-9_-]+( )?");

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
                set_db_name(vector_string);
                break;

            }
            stop = vector_string=="use";
        }
    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};


#endif //ESTESQL_USE_QUERY_H
