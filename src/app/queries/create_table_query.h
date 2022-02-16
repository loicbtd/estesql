#ifndef CREATE_TABLE_QUERY
#define CREATE_TABLE_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/already_existing_table_exception.h"
#include "app/exceptions/missing_or_multiple_primary_key_exception.h"
#include "app/exceptions/insert_duplicate_columns_exception.h"

#include "app/constants/syntax_query.h"
#include "app/constants/string_delimiters.h"

#include "app/helpers/string_utilities.h"
#include "app/helpers/db_table_utilities.h"

#include "app/managers/definition_file.h"

#include "app/models/column_definition.h"

using namespace std;

class create_table_query : public table_related_query {
public:

    create_table_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex("create table [a-z_-]+( )?");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
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