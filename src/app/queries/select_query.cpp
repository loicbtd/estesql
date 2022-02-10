#include "select_query.h"

void select_query::parse() {

    string all_columns("select * from ");

    if (getQuery().find(all_columns) != string::npos) {
        expand();
    }

    string str_regex ("select [a-z_-]+(( )?,( )?[a-z_-]+)* from ");
    str_regex.append(getTableName());

    string where_clause = " where ";
    smatch smatch_;

    if (regex_search(getQuery(), smatch_, regex(where_clause))) {
        str_regex.append(" where [a-z_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z_-]+( (and|or) [a-z_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z_-]+)*( )?;");
    } else {
        str_regex.append(";");
    }

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(SELECT_SYNTAX);
    }

}

void select_query::check() {

    parse();

}

void select_query::expand() {
//TODO retrieve all columns from the tableName and replace '*' by them seprated by ','

    cout << "expand()" << endl;

}

void select_query::execute() {

}
