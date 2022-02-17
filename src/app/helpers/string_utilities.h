#ifndef ESTESQL_STRING_UTILITIES_H
#define ESTESQL_STRING_UTILITIES_H

#include <string>
#include <regex>

#include "app/constants/string_delimiters.h"

#include "app/enumerations/field_type_t.h"


using namespace std;

class string_utilities {

public:

    static string left_trim(const string &);
    static string right_trim(const string &);
    static string trim(const string &);

    static vector<string> convert_parenthesis_string_to_vector_delimiter(string &, char delimiter);

    static string format_string_for_uint8_t(string string_);
    static string delete_quote(string string_);

    static bool contains(string str, string substring);

    static vector<string> convert_string_to_vector_delimiter(string &string_, char delimiter);

    static string erase_substring(string &string_, string substring);

    static string convert_vector_into_string_delimiter(vector<string> vector_, char delimiter);

    static vector<uint8_t> append_vector_uint8t_into_another(vector<uint8_t> vector_first, const vector<uint8_t>& vector_second);

    static vector<vector<uint8_t>>
    static split_vector_with_type_length(vector<uint8_t> vector_full_record, vector<field_type_t> vector_type);

    static vector<uint8_t> convert_vector_of_vector_uint8t_into_vector(const vector<vector<uint8_t>>& vector_to_transform);
};


#endif //ESTESQL_STRING_UTILITIES_H
