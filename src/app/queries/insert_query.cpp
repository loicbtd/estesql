#include "insert_query.h"

void insert_query::parse() {

    string str_regex ("insert into ");
    str_regex.append(get_table_name()).append(" \\\([a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)*\\\) values \\\(('[.\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?)(( )?,( )?('[.\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?))*\\\)( )?;");
    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(INSERT_SYNTAX);
    }

}

void insert_query::check() {

    parse();

    //Todo 1 retrieve all columns from query -> vector<string> OK
    smatch smatch_;
    string columns = "\\\([a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)*\\\) values";
    string columns_str;

    if (regex_search(get_query(), smatch_, regex(columns))) {
        columns_str = smatch_.str();
    }

    columns_str = string_utilities::erase_substring(columns_str, " values");
    vector<string> columns_vector = string_utilities::convert_parenthesis_string_to_vector_delimiter(columns_str, COMA_DELIMITER);

    //Todo 2 retrieve all values -> vector<string> OK

    string values = "values \\\(('[\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?)(( )?,( )?('[\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?))*\\\)";
    string values_str;

    if (regex_search(get_query(), smatch_, regex(values))) {
        values_str = smatch_.str();
    }

    values_str = string_utilities::erase_substring(values_str, "values ");
    vector<string> values_vector = string_utilities::convert_parenthesis_string_to_vector_delimiter(values_str, COMA_DELIMITER);

    //Todo 3.1 check if nb columns == nb values -> size1 == size2 OK
    if (columns_vector.size() != values_vector.size()) {
        throw insert_number_columns_values_exception();
    }

    //Todo 3.2 check if duplicate in columns OK
    if (db_table_utilities::is_duplicate_columns(columns_vector)) {
        throw insert_duplicate_columns_exception();
    }

    //Todo 4 retrieve all columns from definition_file get_table_definition()->get_table_definition() -> vector of column_def
    vector<string> columns_name_from_file = definition_file::get_instance()->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file::get_instance()->get_all_columns_types();


    //Todo 6.1 compare types values/columns from definition_file -> check if "'"
    //Todo 6.2 convert int, float, PK in long long, ... -> in uint8_t + complete string to be have 255 characters
    //Todo 6.3 primary_key management
    //Todo 6.4 put every column in the correct order

    bool is_column_in_insert_query;
    for (int i = 0; i < columns_name_from_file.size(); ++i) {

        is_column_in_insert_query = false;

        for (int j = 0; j < columns_vector.size(); ++j) {

            if (columns_vector[j]==columns_name_from_file[i]) {

                is_column_in_insert_query = true;

                string value = values_vector[j];

                if (
                       (string_utilities::contains(value,"'") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==FLOAT || columns_type_from_file[i]==PRIMARY_KEY))
                    || (string_utilities::contains(value,".") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==PRIMARY_KEY || ((columns_type_from_file[i]!=TEXT && !string_utilities::contains(value,"'")))))
                ) {
                    throw wrong_type_exception();
                }

                if (columns_type_from_file[i]==INT) {

                    record.push_back(stoll(value));
                    offset += 8;

                } else if (columns_type_from_file[i]==FLOAT) {

                    record.push_back(stod(value));
                    offset += 8;

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    key_file* p_key_file = key_file::get_instance();
                    uint64_t p_key(p_key_file->get_next_key());

                    uint64_t p_key_value_proposed(stoull(value));

                    if (p_key_value_proposed >= p_key) {
                        p_key_file->update_key(p_key_value_proposed);
                        record.push_back(p_key_value_proposed);
                    } else {
                        p_key_file->update_key(p_key);
                        record.push_back(p_key);
                    }

                    offset += 8;

                } else if (columns_type_from_file[i]==TEXT) {

                    value = string_utilities::format_string_for_uint8_t(value);
                    vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
                    record.insert(str_to_uint8_t_vector.end(), str_to_uint8_t_vector.begin(), str_to_uint8_t_vector.end());
                    offset += 255;

                }

                break;
            }

        }

        if (!is_column_in_insert_query) {

            if ((columns_type_from_file[i]==INT) || (columns_type_from_file[i]==FLOAT)) {

                    record.push_back(NULL);
                    offset += 8;

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    key_file* p_key_file = key_file::get_instance();
                    uint64_t p_key(p_key_file->get_next_key());

                    p_key_file->update_key(p_key);

                    record.push_back(p_key);
                    offset += 8;

                } else if (columns_type_from_file[i]==TEXT) {

                    string empty_str = string_utilities::format_string_for_uint8_t("''");
                    vector<uint8_t> str_to_uint8_t_vector(empty_str.begin(), empty_str.end());
                    record.insert(str_to_uint8_t_vector.end(), str_to_uint8_t_vector.begin(), str_to_uint8_t_vector.end());
                    offset += 255;

                }
        }

    }



}

void insert_query::expand() {}

void insert_query::execute() {

    cout << "execute()" << endl;
    //Todo execute insert
    content_file* content_file_ = content_file::get_instance();
    content_file_->write_record(record,offset);

}
