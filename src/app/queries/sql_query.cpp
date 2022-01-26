#include "sql_query.h"

void sql_query::parse() {

}

void sql_query::check() {

}

void sql_query::expand() {

}

void sql_query::execute() {

}

const string &sql_query::getQuery() const {
    return query;
}

void sql_query::setQuery(const string &query) {
    sql_query::query = query;
}
