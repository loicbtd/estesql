#include "database_related_query.h"

const string &database_related_query::get_db_name() const {
    return db_name;
}

void database_related_query::set_db_name(const string &dbName) {
    db_name = dbName;
}

database_related_query::database_related_query() {}
