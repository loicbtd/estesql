#ifndef ESTESQL_TABLE_DEFINITION_H
#define ESTESQL_TABLE_DEFINITION_H

#include <vector>

#include "column_definition.h"

using namespace std;

class table_definition {
protected:
    vector<column_definition*> columns;
public:
    const vector<column_definition *> &getColumns() const;
};


#endif //ESTESQL_TABLE_DEFINITION_H
