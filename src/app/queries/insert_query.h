#ifndef INSERT_QUERY
#define INSERT_QUERY

#include <regex>

#include "table_related_query.h"

#include "app/exceptions/sql_invalid_syntax_exception.h"
#include "app/constants/syntax_query.h"

using namespace std;

class insert_query : public table_related_query {
public:

    insert_query(string sql) : table_related_query(sql) {

        smatch smatch_;
        string smatch_regex("insert into [a-z_-]+ ");

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
                setTableName(vector_string);
                break;

            }
            stop = vector_string=="into";
        }

    }

    void parse() override;

    void check() override;

    void expand() override;

    void execute() override;
};

#endif