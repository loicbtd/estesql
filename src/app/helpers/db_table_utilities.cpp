#include "db_table_utilities.h"

struct stat info;

bool db_table_utilities::exists(const char *path) {

    if(stat(path, &info) != 0) {
//        printf("cannot access %s\n", path);
        return false;
    }

    if(info.st_mode & S_IFDIR) {
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
    columns_vector.erase(unique(columns_vector.begin(), columns_vector.end() ), columns_vector.end());
    return size_columns_vector != columns_vector.size();

}

bool db_table_utilities::is_duplicate_columns(vector<column_definition *> columns_def_vector) {

    vector<string> columns_name;
    for (auto col_def: columns_def_vector) {
        columns_name.push_back(col_def->getName());
    }

    return is_duplicate_columns(columns_name);
}
