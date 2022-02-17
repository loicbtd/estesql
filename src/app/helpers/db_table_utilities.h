#ifndef ESTESQL_DB_TABLE_UTILITIES_H
#define ESTESQL_DB_TABLE_UTILITIES_H

#define UINT8_VECTOR_REQUIRED_SIZE 64
#define UINT8_VECTOR_REQUIRED_SIZE_FOR_STRING 255

#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <bitset>

#include "app/models/column_definition.h"

#include "app/exceptions/invalid_uint8_t_vector_size_exception.h"
#include "app/exceptions/wrong_type_exception.h"

#include "string_utilities.h"

using namespace std;

class db_table_utilities {

public:
    static bool exists(const char *);

    static void delete_db_or_table_folder(const string &db_table_path);

    static bool is_duplicate_columns(vector<string>);

    static bool is_duplicate_columns(vector<column_definition *>);

    static vector<uint8_t> int_to_binary_string_to_vector(long long value);

    static vector<uint8_t> primary_key_to_binary_string_to_vector(unsigned long long value);

    static vector<uint8_t> float_to_binary_string_to_vector(double value);

    static unsigned long long uint8_t_vector_to_unsigned_long_long(vector<uint8_t> data);

    static long long uint8_t_vector_to_long_long(vector<uint8_t> data);

    static double uint8_t_vector_to_double(vector<uint8_t> data);

    static string uint8_t_vector_to_string(vector<uint8_t> data);

    static bool compare_INT(long long left, long long right, const string& comp);
    static bool compare_FLOAT(double left, double right, const string& comp);
    static bool compare_STR(const string& left, const string& right, const string& comp);
    static bool compare_P_K(unsigned long long left, unsigned long long right, const string& comp);
};


#endif //ESTESQL_DB_TABLE_UTILITIES_H
