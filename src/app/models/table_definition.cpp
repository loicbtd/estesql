#include "table_definition.h"

const vector<column_definition *> &table_definition::getColumns() const {
    return columns;
}

void table_definition::addColumn(column_definition* column) {
    this->columns.push_back(column);
}

void table_definition::setColumns(const vector<column_definition *> &columns) {

    for (auto column : table_definition::columns) {
        delete column;
    }

    table_definition::columns.clear();

    table_definition::columns = columns;
}
