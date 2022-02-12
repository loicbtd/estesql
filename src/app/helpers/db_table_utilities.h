#ifndef ESTESQL_DB_TABLE_UTILITIES_H
#define ESTESQL_DB_TABLE_UTILITIES_H

#include <string>
#include <sys/stat.h>
#include <filesystem>

#include "app/models/column_definition.h"

using namespace std;

class db_table_utilities {

public:
    static bool exists(const char *);

    static void delete_db_or_table_folder(const string &db_table_path);

    static bool is_duplicate_columns(vector<string>);
    static bool is_duplicate_columns(vector<column_definition*>);
};


#endif //ESTESQL_DB_TABLE_UTILITIES_H
