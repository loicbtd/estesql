#include "string_utilities.h"

 string string_utilities::left_trim(const string &str) {
     return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
}

string string_utilities::right_trim(const string &str) {
    return std::regex_replace(str, std::regex("\\s+$"), std::string(""));
}

string string_utilities::trim(const string &str) {
    return left_trim(right_trim(str));
}