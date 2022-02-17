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
    string data = bitset<sizeof(unsigned long long)>(value).to_string();

    vector<uint8_t> u_data(data.begin(), data.end());

    return u_data;
}

vector<uint8_t> db_table_utilities::float_to_binary_string_to_vector(double value) {
    string data = bitset<sizeof(double)>(value).to_string();

    vector<uint8_t> u_data(data.begin(), data.end());

    return u_data;
}

unsigned long long db_table_utilities::uint8_t_vector_to_unsigned_long_long(vector<uint8_t> data) {
    if(data.size() != UINT8_VECTOR_REQUIRED_SIZE) {
        throw invalid_uint8_t_vector_size_exception();
    }

    return stoull(string(data.begin(), data.end()), nullptr, 2);
}

long long db_table_utilities::uint8_t_vector_to_long_long(vector<uint8_t> data) {
    if(data.size() != UINT8_VECTOR_REQUIRED_SIZE) {
        throw invalid_uint8_t_vector_size_exception();
    }

    return stoll(string(data.begin(), data.end()), nullptr, 2);
}

double db_table_utilities::uint8_t_vector_to_double(vector<uint8_t> data) {
    if(data.size() != UINT8_VECTOR_REQUIRED_SIZE_FOR_DOUBLE_QUICK_WORKAROUND) {
        throw invalid_uint8_t_vector_size_exception();
    }

    return stod(string(data.begin(), data.end()));
}

string db_table_utilities::uint8_t_vector_to_string(vector<uint8_t> data) {
    if(data.size() != UINT8_VECTOR_REQUIRED_SIZE_FOR_STRING) {
        throw invalid_uint8_t_vector_size_exception();
    }

    return string(data.begin(), data.end());
}
