#ifndef DROP_TABLE_QUERY
#define DROP_TABLE_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/non_existing_table_exception.h"

#include "app/constants/syntax_query.h"

#include "app/managers/db_info.h"

#include "app/helpers/db_table_utilities.h"

using namespace std;

class drop_table_query : public table_related_query {
public:

    drop_table_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex("drop table [a-z0-9_-]+( )?");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(DROP_TABLE_SYNTAX);
        }

        stringstream ss(sql);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vector_strings(begin, end);

        bool stop = false;
        for (auto & vector_string : vector_strings) {
            if (stop) {

                vector_string.erase(remove(vector_string.begin(), vector_string.end(), ';'), vector_string.end());
                set_table_name(vector_string);
                break;

            }
            stop = vector_string=="table";
        }

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};

#endif