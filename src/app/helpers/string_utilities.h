#ifndef ESTESQL_STRING_UTILITIES_H
#define ESTESQL_STRING_UTILITIES_H

#include <string>
#include <regex>

#include "app/constants/string_delimiters.h"

using namespace std;

class string_utilities {

public:

    static string left_trim(const string &);
    static string right_trim(const string &);
    static string trim(const string &);

    static vector<string> convert_parenthesis_string_to_vector_delimiter(string &, char delimiter);

    static string format_string_for_uint8_t(string string_);
    static string delete_quote(string string_);
};


#endif //ESTESQL_STRING_UTILITIES_H
