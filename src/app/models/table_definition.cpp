#include "table_definition.h"

const vector<column_definition *> &table_definition::getColumns() const {
    return columns;
}

void table_definition::addColumn(column_definition* column) {
    this->columns.push_back(column);
}
