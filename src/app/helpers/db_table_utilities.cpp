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
