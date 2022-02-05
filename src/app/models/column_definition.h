#ifndef ESTESQL_COLUMN_DEFINITION_H
#define ESTESQL_COLUMN_DEFINITION_H

#include <string>

#include "app/enumerations/field_type_t.h"

using namespace std;

class column_definition {
public:
    field_type_t getType() const;

    void setType(field_type_t type);

    const string &getName() const;

    void setName(const string &name);

protected:
    field_type_t type;
    string name;
};

#endif //ESTESQL_COLUMN_DEFINITION_H
