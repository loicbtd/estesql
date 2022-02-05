#include "create_table_query.h"

void create_table_query::parse() {

    string str_regex ("create table ");
    str_regex.append(getTableName()).append("( )?\([a-z]* (long long|unsigned long long|double|string\([0-9]+\))(,( )?[a-z]* (long long|unsigned long long|double|string\([0-9]+\)))*\)( )?;");

    regex create_table_regex (str_regex);

    if (!regex_match(getQuery(),create_table_regex)) {
        throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
    }

}

void create_table_query::check() {

}

void create_table_query::expand() {

}

void create_table_query::execute() {

}

