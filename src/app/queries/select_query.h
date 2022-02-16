#ifndef SELECT_QUERY
#define SELECT_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/non_existing_table_exception.h"

#include "app/constants/syntax_query.h"
#include "app/constants/string_delimiters.h"

#include "app/helpers/db_table_utilities.h"
#include "app/helpers/string_utilities.h"

#include "app/managers/db_info.h"

using namespace std;

class select_query : public table_related_query {
public:

    select_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex(" from [a-z0-9_-]+( )?");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(SELECT_SYNTAX);
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
            stop = vector_string=="from";
        }

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif