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

vector<string> string_utilities::convert_parenthesis_string_to_vector_delimiter(string &string_, char delimiter) {

    string_.erase(remove(string_.begin(), string_.end(), PARENTHESIS_OPEN_DELIMITER), string_.end());
    string_.erase(remove(string_.begin(), string_.end(), PARENTHESIS_CLOSE_DELIMITER), string_.end());

    return convert_string_to_vector_delimiter(string_, delimiter);
}

vector<string> string_utilities::convert_string_to_vector_delimiter(string &string_, char delimiter) {

    stringstream str_stream(string_);
    vector<string> vector_str;

    while(str_stream.good()) {
        string substr;
        getline(str_stream, substr, delimiter);
        vector_str.push_back(string_utilities::trim(substr));
    }

    return vector_str;
}

string string_utilities::erase_substring(string &string_, string substring) {

    size_t pos = string_.find(substring);

    if (pos != std::string::npos) {
        string_.erase(pos, substring.length());
    }

    return string_;

}

string string_utilities::format_string_for_uint8_t(string string_) {

    string tmp = delete_quote(string_);
    unsigned size = tmp.size();
    tmp.resize (size + (255-size), ' ');
    return tmp;

}

string string_utilities::delete_quote(string string_) {

    string tmp = string_;
    tmp.erase(std::remove(tmp.begin(), tmp.end(), '\''), tmp.end());
    return tmp;

}

bool string_utilities::contains(string str, string substring) {
    return str.find(substring) != std::string::npos;
}


string string_utilities::convert_vector_into_string_delimiter(vector<string> vector_, char delimiter) {

    string string_conv("");

    for (int i=0; i < vector_.size(); ++i) {
        string_conv.append(vector_[i]);
        if (i != vector_.size()-1) {
            string_conv.append(reinterpret_cast<const char *>(delimiter));
        }
    }

    return string_conv;
}