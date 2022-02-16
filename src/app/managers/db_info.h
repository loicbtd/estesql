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
    const string &get_db_parent_folder_path() const;

    void set_db_parent_folder_path(const string &dbParentFolderPath);

public:
    const string &get_db_name() const;

    void set_db_name(const string &dbName);


    db_info() {}

    static db_info* db_info_;

    static db_info *get_instance();

    const string &get_current_db_path() const;

    void set_current_db_path(const string &currentDbPath);

};


#endif //ESTESQL_DB_INFO_H
