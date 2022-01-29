#include "db_info.h"

const string &db_info::getCurrentDbPath() const {
    return current_db_path;
}

void db_info::setCurrentDbPath(const string &currentDbPath) {
    current_db_path = currentDbPath;
}


db_info* db_info::db_info_= nullptr;;


db_info *db_info::GetInstance() {
    if(db_info_==nullptr){
        db_info_ = new db_info();
    }
    return db_info_;
}