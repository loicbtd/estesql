#ifndef ESTESQL_TABLE_FILE_H
#define ESTESQL_TABLE_FILE_H

#include <string>
#include <filesystem>
#include <fstream>
#include <cstring>
#include <cstddef>

#include "db_info.h"
#include "app/constants/test_strings.h"
#include "app/constants/file_extensions.h"
#include "app/exceptions/file_is_not_open_exception.h"
#include "app/exceptions/inability_to_check_if_file_exists_exception.h"
#include "app/exceptions/inability_to_create_file_exception.h"
#include "app/exceptions/inability_to_create_directory_exception.h"
#include "app/exceptions/inability_to_open_file_exception.h"

using namespace std;

class table_file {
protected:
    string source_file;
    string file_extension;
    fstream file;

public:
    table_file(string extension);

    const string &get_current_table_name() const;

    void set_current_table_name(const string &source);

    bool exists();

    virtual void open();

    void close();
};

#endif //ESTESQL_TABLE_FILE_H
