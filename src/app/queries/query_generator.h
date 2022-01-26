#ifndef ESTESQL_QUERY_GENERATOR_H
#define ESTESQL_QUERY_GENERATOR_H

#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "sql_query.h"

#include "create_table_query.h"
#include "create_database_query.h"
#include "drop_table_query.h"
#include "drop_database_query.h"
#include "select_query.h"
#include "insert_query.h"
#include "update_query.h"
#include "delete_query.h"
#include "use_query.h"

#include "app/constants/string_key_words.h"
#include "app/enumerations/query_type.h"
#include "app/constants/string_delimiters.h"

#include "app/exceptions/query_size_exception.h"
#include "app/exceptions/create_drop_table_or_db_exception.h"
#include "app/exceptions/unknown_query_exception.h"

using namespace std;

class query_generator {

public:
    static unique_ptr<sql_query> generate_query(const string&);
};


#endif //ESTESQL_QUERY_GENERATOR_H
