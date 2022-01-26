#include "table_related_query.h"

const string &table_related_query::getTableName() const {
    return table_name;
}

void table_related_query::setTableName(const string &tableName) {
    table_name = tableName;
}
