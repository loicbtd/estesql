#ifndef ESTESQL_DB_INFO_H
#define ESTESQL_DB_INFO_H

#include <string>

using namespace std;

class db_info {

private:
    string current_db_path;
    string db_name;
    string db_parent_folder_path;
public:
    const string &getDbParentFolderPath() const;

    void setDbParentFolderPath(const string &dbParentFolderPath);

public:
    const string &getDbName() const;

    void setDbName(const string &dbName);


    db_info() {}

    static db_info* db_info_;

    static db_info *get_instance();

    const string &getCurrentDbPath() const;

    void setCurrentDbPath(const string &currentDbPath);

};


#endif //ESTESQL_DB_INFO_H
