#include "column_definition.h"

field_type_t column_definition::getType() const {
    return type;
}

void column_definition::setType(field_type_t type) {
    column_definition::type = type;
}

const string &column_definition::getName() const {
    return name;
}

void column_definition::setName(const string &name) {
    column_definition::name = name;
}


