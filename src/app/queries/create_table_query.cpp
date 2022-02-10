#include "create_table_query.h"

void create_table_query::parse() {

    string str_regex ("create table ");
    str_regex.append(getTableName()).append("( )?\([a-z_-]* (int|primarey_key|float|text)(,( )?[a-z_-]* (int|primarey_key|float|text))*\)( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
    }

}

void create_table_query::check() {

    parse();

}

void create_table_query::expand() {

}

void create_table_query::execute() {

}

