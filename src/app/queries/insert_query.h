#ifndef INSERT_QUERY
#define INSERT_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/exceptions/insert_number_columns_values_exception.h"
#include "app/exceptions/insert_duplicate_columns_exception.h"
#include "app/exceptions/wrong_type_exception.h"
#include "app/exceptions/non_existing_table_exception.h"

#include "app/constants/syntax_query.h"
#include "app/constants/string_delimiters.h"

#include "app/helpers/db_table_utilities.h"
#include "app/helpers/string_utilities.h"
#include "app/helpers/file_set_up.h"

#include "app/managers/definition_file.h"
#include "app/managers/key_file.h"
#include "app/managers/content_file.h"

#include "app/models/column_definition.h"

using namespace std;

class insert_query : public table_related_query {
protected:
    vector<uint8_t> record;
public:
    const vector<uint8_t> &get_record() const;

protected:
    uint32_t length;

public:

    insert_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex("insert into [a-z0-9_-]+ ");

        if (!regex_search(sql, smatch_, regex(smatch_regex))) {
            throw slq_invalid_syntax_exception(INSERT_SYNTAX);
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
            stop = vector_string=="into";
        }

        length = 0;

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;

};

#endif