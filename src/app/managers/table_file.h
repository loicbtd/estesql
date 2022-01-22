#ifndef ESTESQL_TABLE_FILE_H
#define ESTESQL_TABLE_FILE_H

#include <string>

using namespace std;

class table_file {

private:
    string source_file;

    virtual bool exists();
    virtual void open();
    virtual void close();

};


#endif //ESTESQL_TABLE_FILE_H
