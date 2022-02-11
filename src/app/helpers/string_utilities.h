#ifndef ESTESQL_STRING_UTILITIES_H
#define ESTESQL_STRING_UTILITIES_H

#include <string>
#include <regex>

using namespace std;

class string_utilities {

public:

    static string left_trim(const string &);
    static string right_trim(const string &);
    static string trim(const string &);

};


#endif //ESTESQL_STRING_UTILITIES_H
