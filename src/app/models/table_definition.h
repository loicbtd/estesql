#ifndef ESTESQL_TABLE_DEFINITION_H
#define ESTESQL_TABLE_DEFINITION_H

#include <vector>

#include "column_definition.h"

using namespace std;

class table_definition {
protected:
    vector<column_definition*> columns;

public:
    table_definition(vector<column_definition*> columns_): columns(columns_) {}


    void set_columns(const vector<column_definition *> &columns);
    const vector<column_definition *> &get_columns() const;

    void add_column(column_definition* column);

};


#endif //ESTESQL_TABLE_DEFINITION_H
