#ifndef ESTESQL_APP_H
#define ESTESQL_APP_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <map>

#include "app/queries/sql_query.h"
#include "app/queries/query_generator.h"

#include "app/managers/db_info.h"

#include "app/helpers/db_table_utilities.h"

#include "app/enumerations/query_type.h"

#include "app/constants/inline_parameters.h"

#include "app/exceptions/custom_exception.h"

#include "app/tests/db_utilities_should.h"
#include "app/tests/definition_file_should.h"
#include "app/tests/index_file_should.h"
#include "app/tests/table_file_should.h"

using namespace std;

class app {

public:
    void start(int argc, char const *argv[]);

    bool usage(int argc, char const *argv[], db_info *);
};

#endif //ESTESQL_APP_H