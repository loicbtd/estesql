#ifndef ESTESQL_FILE_SET_UP_H
#define ESTESQL_FILE_SET_UP_H

#include <string>

#include "app/managers/definition_file.h"
#include "app/managers/content_file.h"
#include "app/managers/index_file.h"
#include "app/managers/key_file.h"

using namespace std;

class file_set_up {

public:
    static void set_up_source_file(const string& source_file);

};


#endif //ESTESQL_FILE_SET_UP_H
