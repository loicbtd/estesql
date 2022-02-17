#include "db_table_utilities.h"

struct stat info;

bool db_table_utilities::exists(const char *path) {

    if (stat(path, &info) != 0) {
//        printf("cannot access %s\n", path);
        return false;
    }

    if (info.st_mode & S_IFDIR) {
//        printf("%s is a directory\n", path);
        return true;
    }

//    printf("%s is no directory or not exists\n", path);
    return false;
}

void db_table_utilities::delete_db_or_table_folder(const string &db_table_path) {
    filesystem::remove_all(db_table_path);
}

bool db_table_utilities::is_duplicate_columns(vector<string> columns_vector) {

    unsigned long long size_columns_vector = columns_vector.size();
    columns_vector.erase(unique(columns_vector.begin(), columns_vector.end()), columns_vector.end());
    return size_columns_vector != columns_vector.size();

}

bool db_table_utilities::is_duplicate_columns(vector<column_definition *> columns_def_vector) {

    vector<string> columns_name;
    for (auto col_def: columns_def_vector) {
        columns_name.push_back(col_def->get_name());
    }

    return is_duplicate_columns(columns_name);
}

vector<uint8_t> db_table_utilities::int_to_binary_string_to_vector(long long value) {
    string data = bitset<sizeof(long long)>(value).to_string();

    vector<uint8_t> u_data(data.begin(), data.end());

    return u_data;
}

vector<uint8_t> db_table_utilities::primary_key_to_binary_string_to_vector(unsigned long long value) {
    string data = string_utilities::format_string_for_uint8_t(bitset<sizeof(unsigned long long)>(value).to_string());

    vector<uint8_t> u_data(data.begin(), data.end());

    return u_data;
}

vector<uint8_t> db_table_utilities::float_to_binary_string_to_vector(double value) {
    string data = string_utilities::format_string_for_uint8_t(bitset<sizeof(double)>(value).to_string());

    vector<uint8_t> u_data(data.begin(), data.end());

    return u_data;
}
