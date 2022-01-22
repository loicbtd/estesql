#include "db_info.h"

const string &db_info::getCurrentDbPath() const {
    return current_db_path;
}

void db_info::setCurrentDbPath(const string &currentDbPath) {
    current_db_path = currentDbPath;
}
