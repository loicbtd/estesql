#include "delete_query.h"

void delete_query::parse() {

    string str_regex ("delete from ");
    str_regex.append(get_table_name());

    string where_clause = " where ";
    smatch smatch_;

    if (regex_search(getQuery(), smatch_, regex(where_clause))) {
        str_regex.append(" where [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+)*( )?;");
    } else {
        str_regex.append("( )?;");
    }

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DELETE_SYNTAX);
    }

}

void delete_query::check() {

    parse();

}

void delete_query::expand() {

}

void delete_query::execute() {

}
