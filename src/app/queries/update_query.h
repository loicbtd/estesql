#ifndef UPDATE_QUERY
#define UPDATE_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/non_existing_table_exception.h"
#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/update_primary_key_exception.h"

#include "app/constants/syntax_query.h"

#include "app/models/where_clause.h"

#include "app/managers/db_info.h"
#include "app/managers/definition_file.h"

#include "app/helpers/db_table_utilities.h"
#include "app/helpers/build_where_clause.h"
#include "app/helpers/file_set_up.h"

using namespace std;

class update_query : public table_related_query {
private:
    bool is_where_clause;
    where_clause where_clause;
    vector<pair<bool, vector<uint8_t>>> vector_pair_is_modify_value;

public:

    update_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex("update [a-z0-9_-]+( )?");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(UPDATE_SYNTAX);
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
                file_set_up::set_up_source_file(get_table_name());

                break;

            }
            stop = vector_string=="update";
        }

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

    bool is_where_clause_get() const;

    void set_is_where_clause(bool isWhereClause);

    const class where_clause &get_where_clause() const;

    void set_where_clause(const class where_clause &whereClause);

};

#endif