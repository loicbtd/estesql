#include "table_related_query.h"

const string &table_related_query::get_table_name() const {
    return table_name;
}

void table_related_query::set_table_name(const string &tableName) {
    table_name = tableName;
}
