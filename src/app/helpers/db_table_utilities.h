#ifndef ESTESQL_DB_TABLE_UTILITIES_H
#define ESTESQL_DB_TABLE_UTILITIES_H

#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <bitset>

#include "app/models/column_definition.h"
#include "string_utilities.h"

using namespace std;

class db_table_utilities {

public:
    static bool exists(const char *);

    static void delete_db_or_table_folder(const string &db_table_path);

    static bool is_duplicate_columns(vector<string>);

    static bool is_duplicate_columns(vector<column_definition *>);

    static vector<uint8_t> int_to_vector(long long value);

    static vector<uint8_t> primary_key_to_vector(unsigned long long value);

    static vector<uint8_t> float_to_vector(double value);
};


#endif //ESTESQL_DB_TABLE_UTILITIES_H
