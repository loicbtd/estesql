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

    definition_file* definition_file = definition_file::get_instance();

    if (!definition_file->exists()) {
        throw non_existing_table_exception();
    }

    // 1 retrieve all columns from query -> vector<string> OK
    smatch smatch_;
    string columns = "\\\([a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)*\\\) values";
    string columns_str;

    if (regex_search(get_query(), smatch_, regex(columns))) {
        columns_str = smatch_.str();
    }

    columns_str = string_utilities::erase_substring(columns_str, " values");
    vector<string> columns_vector = string_utilities::convert_parenthesis_string_to_vector_delimiter(columns_str, COMA_DELIMITER);

    // 2 retrieve all values -> vector<string> OK

    string values = "values \\\(('[\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?)(( )?,( )?('[\\\sa-z0-9_-]{0,255}'|[0-9]+(.[0-9]+)?))*\\\)";
    string values_str;

    if (regex_search(get_query(), smatch_, regex(values))) {
        values_str = smatch_.str();
    }

    values_str = string_utilities::erase_substring(values_str, "values ");
    vector<string> values_vector = string_utilities::convert_parenthesis_string_to_vector_delimiter(values_str, COMA_DELIMITER);

    // 3.1 check if nb columns == nb values -> size1 == size2 OK
    if (columns_vector.size() != values_vector.size()) {
        throw insert_number_columns_values_exception();
    }

    // 3.2 check if duplicate in columns OK
    if (db_table_utilities::is_duplicate_columns(columns_vector)) {
        throw insert_duplicate_columns_exception();
    }

    // 4 retrieve all columns from definition_file get_table_definition()->get_table_definition() -> vector of column_def
    vector<string> columns_name_from_file = definition_file::get_instance()->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file::get_instance()->get_all_columns_types();

    // 5 check if columns in query are in definition_file
    for (auto & i : columns_vector) {
        bool is_column_in_definition_file = false;
        for (auto & j : columns_name_from_file) {
            if (i == j) {
                is_column_in_definition_file = true;
                break;
            }
        }
        if (!is_column_in_definition_file) {
            throw column_non_existing_exception();
        }
    }

    // 6.1 compare types values/columns from definition_file -> check if "'"
    // 6.2 convert int, float, PK in long long, ... -> in uint8_t + complete string to be have 255 characters
    // 6.3 primary_key management
    // 6.4 put every column in the correct order
    bool is_column_in_insert_query;
    for (int i = 0; i < columns_name_from_file.size(); ++i) {

        is_column_in_insert_query = false;
        vector<uint8_t> temp;

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

                    temp = db_table_utilities::int_to_binary_string_to_vector(stoll(value));
                    record = string_utilities::append_vector_uint8t_into_another(record, temp);

                    length += 8;

                } else if (columns_type_from_file[i]==FLOAT) {

                    temp = db_table_utilities::float_to_binary_string_to_vector(stod(value));
                    record = string_utilities::append_vector_uint8t_into_another(record, temp);

                    length += 8;

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    key_file* p_key_file = key_file::get_instance();
                    uint64_t p_key(p_key_file->get_next_key());

                    uint64_t p_key_value_proposed(stoull(value));

                    if (p_key_value_proposed >= p_key) {

                        temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key_value_proposed);
                        record = string_utilities::append_vector_uint8t_into_another(record, temp);

                        p_key_file->update_key(p_key_value_proposed);

                    } else {

                        temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key);
                        record = string_utilities::append_vector_uint8t_into_another(record, temp);

                        p_key_file->update_key(p_key);

                    }

                    length += 8;

                } else if (columns_type_from_file[i]==TEXT) {

                    value = string_utilities::format_string_for_uint8_t(value);
                    vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
                    record = string_utilities::append_vector_uint8t_into_another(record, str_to_uint8_t_vector);
                    length += 255;

                }

                break;
            }

        }

        if (!is_column_in_insert_query) {

            if (columns_type_from_file[i]==INT) {

                temp = db_table_utilities::int_to_binary_string_to_vector(NULL);
                record = string_utilities::append_vector_uint8t_into_another(record, temp);

                length += 8;

            } else if (columns_type_from_file[i]==FLOAT) {

                temp = db_table_utilities::float_to_binary_string_to_vector(NULL);
                record = string_utilities::append_vector_uint8t_into_another(record, temp);

                length += 8;

            } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                key_file* p_key_file = key_file::get_instance();
                uint64_t p_key(p_key_file->get_next_key());

                temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key);
                record = string_utilities::append_vector_uint8t_into_another(record, temp);

                p_key_file->update_key(p_key);

                length += 8;

            } else if (columns_type_from_file[i]==TEXT) {

                string empty_str = string_utilities::format_string_for_uint8_t("''");
                vector<uint8_t> str_to_uint8_t_vector(empty_str.begin(), empty_str.end());
                record = string_utilities::append_vector_uint8t_into_another(record, str_to_uint8_t_vector);
                length += 255;

            }
        }

    }



}

void insert_query::expand() {}

void insert_query::execute() {

    // execute insert
    content_file* content_file_ = content_file::get_instance();
    index_file* index_file = index_file::get_instance();
    vector<uint8_t> blop = get_record();
    content_file_->write_record(blop, index_file->get_first_inactive_index());

}

const vector<uint8_t> &insert_query::get_record() const {
    return record;
}


