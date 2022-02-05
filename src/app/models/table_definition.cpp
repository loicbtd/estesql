#include "table_definition.h"

const vector<column_definition *> &table_definition::getColumns() const {
    return columns;
}
