#include "drop_table_query.h"

void drop_table_query::parse() {

    string str_regex ("drop table ");
    str_regex.append(getTableName()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DROP_TABLE_SYNTAX);
    }

}

void drop_table_query::check() {

}

void drop_table_query::expand() {

}

void drop_table_query::execute() {

}
