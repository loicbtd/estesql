#ifndef ESTESQL_TABLE_FILE_H
#define ESTESQL_TABLE_FILE_H

#include <string>
#include <fstream>

using namespace std;

class table_file {
protected:
    string source_file;
    fstream file;

public:
    table_file(string file): source_file(file) {}
    const string &getSourceFile() const;
    void setSourceFile(const string &sourceFile);
    virtual bool exists() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
};


#endif //ESTESQL_TABLE_FILE_H
