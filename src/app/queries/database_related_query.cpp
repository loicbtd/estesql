#include "database_related_query.h"

const string &database_related_query::getDbName() const {
    return db_name;
}

void database_related_query::setDbName(const string &dbName) {
    db_name = dbName;
}
