#include "create_table_query.h"

void create_table_query::parse() {

    string str_regex ("create table ");
    str_regex.append(getTableName()).append(" \\\([a-z_-]+ (int|primary_key|float|text)(( )?,( )?[a-z_-]+ (int|primary_key|float|text))*\\\)( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
    }

}

void create_table_query::check() {

    parse();

    smatch smatch_;
    string columns = "\\\([a-z_-]* (int|primarey_key|float|text)(,( )?[a-z_-]* (int|primarey_key|float|text))*\\\)";
    if (regex_search(getQuery(), smatch_, regex(columns))) {
        cout << smatch_[0] << endl;
    }

    //Todo 1 retrieve columns_names
    //Todo 2 retrieve columns_type
    //Todo 3 create column_definition* with each
    //Todo 4 create vector of column_definition*


}

void create_table_query::expand() {

}

void create_table_query::execute() {

}

