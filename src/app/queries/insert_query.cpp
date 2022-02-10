#include "insert_query.h"

void insert_query::parse() {

    string str_regex ("insert into ");
    str_regex.append(getTableName()).append(" \\\([a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)*\\\) values \\\(('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*\\\)( )?;");
    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(INSERT_SYNTAX);
    }

}

void insert_query::check() {

    parse();

}

void insert_query::expand() {

}

void insert_query::execute() {

}
