#ifndef ESTESQL_WHERE_CLAUSE_H
#define ESTESQL_WHERE_CLAUSE_H

#include <string>
#include <vector>

#include "app/helpers/db_table_utilities.h"

using namespace std;

class where_clause {

private:
    vector<pair<string, vector<string>>> elements;
    string type;

public:
    where_clause() {}

    where_clause(vector<pair<string, vector<string>>> elements_, string type_) : elements(elements_), type(type_) {}

    const vector<pair<string, vector<string>>> &get_elements() const;

    void set_elements(const vector<pair<string, vector<string>>> &elements);

    const string &get_type() const;

    void set_type(const string &type);

    bool is_where_clause_apply(vector<vector<uint8_t>> record, const vector<string>& columns_names, const vector<field_type_t>& columns_types);

};

#endif //ESTESQL_WHERE_CLAUSE_H
