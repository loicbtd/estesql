#include "drop_database_query.h"

void drop_database_query::parse() {

    string str_regex ("drop (database|db) ");
    str_regex.append(getDbName()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DROP_DB_SYNTAX);
    }

}

void drop_database_query::check() {

}

void drop_database_query::expand() {

}

void drop_database_query::execute() {

}
