#include "db_info.h"

const string &db_info::get_current_db_path() const {
    return current_db_path;
}

void db_info::set_current_db_path(const string &currentDbPath) {
    current_db_path = currentDbPath;
}

const string &db_info::get_db_name() const {
    return db_name;
}

void db_info::set_db_name(const string &dbName) {
    db_name = dbName;
}

const string &db_info::get_db_parent_folder_path() const {
    return db_parent_folder_path;
}

void db_info::set_db_parent_folder_path(const string &dbParentFolderPath) {
    db_parent_folder_path = dbParentFolderPath;
}

db_info* db_info::db_info_= nullptr;;


db_info *db_info::get_instance() {
    if(db_info_==nullptr){
        db_info_ = new db_info();
    }
    return db_info_;
}



