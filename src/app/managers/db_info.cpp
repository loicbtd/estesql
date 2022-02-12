#include "db_info.h"

const string &db_info::getCurrentDbPath() const {
    return current_db_path;
}

void db_info::setCurrentDbPath(const string &currentDbPath) {
    current_db_path = currentDbPath;
}

const string &db_info::getDbName() const {
    return db_name;
}

void db_info::setDbName(const string &dbName) {
    db_name = dbName;
}

const string &db_info::getDbParentFolderPath() const {
    return db_parent_folder_path;
}

void db_info::setDbParentFolderPath(const string &dbParentFolderPath) {
    db_parent_folder_path = dbParentFolderPath;
}

db_info* db_info::db_info_= nullptr;;


db_info *db_info::get_instance() {
    if(db_info_==nullptr){
        db_info_ = new db_info();
    }
    return db_info_;
}



