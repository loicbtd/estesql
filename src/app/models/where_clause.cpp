#include "where_clause.h"

const vector<pair<string, vector<string>>> &where_clause::get_elements() const {
    return elements;
}

void where_clause::set_elements(const vector<pair<string, vector<string>>> &elements) {
    where_clause::elements = elements;
}

const string &where_clause::get_type() const {
    return type;
}

void where_clause::set_type(const string &type) {
    where_clause::type = type;
}

bool where_clause::is_where_clause_apply(vector<uint8_t> record, vector<string> columns_names) {
    return false;
}
