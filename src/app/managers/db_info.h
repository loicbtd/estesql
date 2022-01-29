#ifndef ESTESQL_DB_INFO_H
#define ESTESQL_DB_INFO_H

#include <string>

using namespace std;

class db_info {

private:
    string current_db_path;

public:

    db_info() {}

    static db_info* db_info_;

    static db_info *GetInstance();

    const string &getCurrentDbPath() const;

    void setCurrentDbPath(const string &currentDbPath);

};


#endif //ESTESQL_DB_INFO_H
