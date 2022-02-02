#include "db_utilities.h"

struct stat info;

bool db_utilities::exists(const char *path) {

    if(stat(path, &info) != 0) {
//        printf("cannot access %s\n", path);
        return false;
    }

    if(info.st_mode & S_IFDIR) {
//        printf("%s is a directory\n", path);
        return true;
    }

    printf("%s is no directory or not exists\n", path);
    return false;


}
