#ifndef ESTESQL_WHERE_CLAUSE_H
#define ESTESQL_WHERE_CLAUSE_H

#include <string>
#include <vector>

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

    bool is_where_clause_apply(vector<uint8_t> record, vector<string> columns_names);

};

#endif //ESTESQL_WHERE_CLAUSE_H
