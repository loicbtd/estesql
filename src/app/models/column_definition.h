#ifndef ESTESQL_COLUMN_DEFINITION_H
#define ESTESQL_COLUMN_DEFINITION_H

#include <string>

#include "app/enumerations/field_type_t.h"

using namespace std;

class column_definition {
public:

    column_definition() {}

    field_type_t get_type() const;

    void set_type(field_type_t type);

    const string &get_name() const;

    void set_name(const string &name);

protected:
    field_type_t type;
    string name;
};

#endif //ESTESQL_COLUMN_DEFINITION_H
