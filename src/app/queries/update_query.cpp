#include "update_query.h"

void update_query::parse() {

    string str_regex ("update ");
    str_regex.append(get_table_name()).append(" set [a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?[a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*");

    string where_clause = " where ";
    smatch smatch_;

    if (regex_search(get_query(), smatch_, regex(where_clause))) {
        str_regex.append(" where [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+)*( )?;");
    } else {
        str_regex.append(";");
    }

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(UPDATE_SYNTAX);
    }

}

void update_query::check() {

    parse();

}

void update_query::expand() {

}

void update_query::execute() {

}
