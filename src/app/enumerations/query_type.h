#ifndef ESTESQL_QUERY_TYPE_H
#define ESTESQL_QUERY_TYPE_H

#include <string>

#define NUMBER_OF_QUERIES 6

using namespace std;

enum query_type_enum {
    create, select, insert, update, delete_, drop, use
};

static const char *enum_str[] =
        { "create", "select", "insert", "update", "delete", "drop", "use" };

//string getStringForEnum(int enum_val) {
//    string tmp(enum_str[enum_val]);
//    return tmp;
//}



#endif //ESTESQL_QUERY_TYPE_H
