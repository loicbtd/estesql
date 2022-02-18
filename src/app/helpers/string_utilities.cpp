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

    size_t pos = string::npos;

    while ((pos = string_.find(substring) )!= std::string::npos) {
        // If found then erase it from string
        string_.erase(pos, substring.length());
    }

    return string_;

}

string string_utilities::format_string_for_uint8_t(string string_) {

    string tmp = delete_quote(string_);
    unsigned size = tmp.size();
    tmp.resize (255, ' ');
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

    for (int i=0; i < vector_.size()-1; ++i) {
        string_conv.append(vector_.at(i) + delimiter);
    }

    string_conv.append(vector_.at(vector_.size()-1));

    return string_conv;
}

vector<uint8_t> string_utilities::append_vector_uint8t_into_another(vector<uint8_t> vector_first, const vector<uint8_t>& vector_second) {

    vector<uint8_t> vector_temp(vector_first);

    for (auto element: vector_second) {
        vector_temp.push_back(element);
    }

    return vector_temp;

}

vector<vector<uint8_t>> string_utilities::split_vector_with_type_length(vector<uint8_t> vector_full_record, vector<field_type_t> vector_type) {

    vector<vector<uint8_t>> result;

    int cursor = 0;
    for (int i = 0; i < vector_type.size(); ++i) {

        int length;
        switch (vector_type.at(i)) {
            case INT:
            case FLOAT:
            case PRIMARY_KEY:
                length = 64;
                break;
            case TEXT:
                length = 255;
                break;
        }

        int start = cursor;
        int end = cursor + length;
        vector<uint8_t> temp;
        for (int j = start; j < end; ++j) {
            temp.push_back(vector_full_record.at(j));
        }

        result.push_back(temp);
        cursor = end;
    }

    return result;
}

vector<uint8_t> string_utilities::convert_vector_of_vector_uint8t_into_vector(const vector<vector<uint8_t>>& vector_to_transform) {

    vector<uint8_t> result;

    for (const auto& vector_uint8_t: vector_to_transform) {
        for (auto element: vector_uint8_t) {
            result.push_back(element);
        }
    }

    return result;
}


string string_utilities::get_value_of_vector(const vector<uint8_t>& vector_record_column, field_type_t type) {

    string result;

    switch (type) {
        case INT:
            result = to_string(db_table_utilities::uint8_t_vector_to_long_long(vector_record_column));
            break;
        case FLOAT:
            result = to_string(db_table_utilities::uint8_t_vector_to_double(vector_record_column));
            break;
        case PRIMARY_KEY:
            result = to_string(db_table_utilities::uint8_t_vector_to_unsigned_long_long(vector_record_column));
            break;
        case TEXT:
            result = db_table_utilities::uint8_t_vector_to_string(vector_record_column);
            result.resize(WIDTH_COLUMN_STR);
            break;
    }

    return result;

}