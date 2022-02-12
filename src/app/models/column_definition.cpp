#include "column_definition.h"

field_type_t column_definition::get_type() const {
    return type;
}

void column_definition::set_type(field_type_t type) {
    column_definition::type = type;
}

const string &column_definition::get_name() const {
    return name;
}

void column_definition::set_name(const string &name) {
    column_definition::name = name;
}


