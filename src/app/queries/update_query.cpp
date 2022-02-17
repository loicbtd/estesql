#include "update_query.h"
#include "app/exceptions/wrong_type_exception.h"

void update_query::parse() {

    string str_regex ("update ");
    str_regex.append(get_table_name()).append(" set [a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?[a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*");

    string where_clause_str = " where ";
    smatch smatch_;

    if (regex_search(get_query(), smatch_, regex(where_clause_str))) {

        str_regex.append(" where [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+)*( )?;");
        set_is_where_clause(true);

    } else {

        str_regex.append("( )?;");
        set_is_where_clause(false);

    }

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(UPDATE_SYNTAX);
    }

}

void update_query::check() {

    parse();

    definition_file* definition_file = definition_file::get_instance();

    if (!definition_file->exists()) {
        throw non_existing_table_exception();
    }

    string regx_str = "set [a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?[a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*";
    smatch all;
    regex_search(get_query(), all, regex(regx_str));
    string columns_str = all.str();

    columns_str = string_utilities::erase_substring(columns_str, "set ");
    vector<string> columns_update_vector = string_utilities::convert_string_to_vector_delimiter(columns_str, COMA_DELIMITER);

    vector<pair<string,string>> columns_values_vector;
    for (auto column: columns_update_vector) {
        vector<string> temp = string_utilities::convert_string_to_vector_delimiter(column, EQUAL_DELIMITER);
        columns_values_vector.emplace_back(temp.at(0), temp.at(1));
    }

    // 2.2 retrieve all columns from definition_file
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    // check if all columns are in the table
    for(const auto& column_query : columns_values_vector) {
        bool is_column = false;
        for (const auto& column_name : columns_name_from_file) {
            if (column_query.first == column_name) {
                is_column = true;
                break;
            }
        }

        if (!is_column) {
            throw column_non_existing_exception();
        }
//        cout << "pair(" << column_query.first << "," << column_query.second << ")" << endl;
    }

    //Todo check if all types correspond to values
    bool is_column_in_update_query;
//    vector<pair<bool, vector<uint8_t>>> vector_pair_is_modify_value;
//    vector<uint8_t> updated_record;
    for (int i = 0; i < columns_name_from_file.size(); ++i) {

        is_column_in_update_query = false;
        vector<uint8_t> temp;

        for (const auto& column_query : columns_values_vector) {

            if (column_query.first==columns_name_from_file[i]) {

                is_column_in_update_query = true;

                string value = column_query.second;

                if (
                        (string_utilities::contains(value,"'") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==FLOAT || columns_type_from_file[i]==PRIMARY_KEY))
                        || (string_utilities::contains(value,".") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==PRIMARY_KEY || ((columns_type_from_file[i]!=TEXT && !string_utilities::contains(value,"'")))))
                        ) {
                    throw wrong_type_exception();
                }

                if (columns_type_from_file[i]==INT) {

                    temp = db_table_utilities::int_to_binary_string_to_vector(stoll(value));
//                    updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

                } else if (columns_type_from_file[i]==FLOAT) {

                    temp = db_table_utilities::float_to_binary_string_to_vector(stod(value));
//                    updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    key_file* p_key_file = key_file::get_instance();
                    uint64_t p_key(p_key_file->get_next_key());

                    uint64_t p_key_value_proposed(stoull(value));

                    if (p_key_value_proposed >= p_key) {

                        temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key_value_proposed);
//                        updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

                        p_key_file->update_key(p_key_value_proposed);

                    } else {

                        temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key);
//                        updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

                        p_key_file->update_key(p_key);

                    }

                } else if (columns_type_from_file[i]==TEXT) {

                    value = string_utilities::format_string_for_uint8_t(value);
                    vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
//                    updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, str_to_uint8_t_vector);

                }

                break;
            }

        }

        if (!is_column_in_update_query) {

            if (columns_type_from_file[i]==INT) {

                temp = db_table_utilities::int_to_binary_string_to_vector(NULL);
//                updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

            } else if (columns_type_from_file[i]==FLOAT) {

                temp = db_table_utilities::float_to_binary_string_to_vector(NULL);
//                updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

            } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                key_file* p_key_file = key_file::get_instance();
                uint64_t p_key(p_key_file->get_next_key());

                temp = db_table_utilities::primary_key_to_binary_string_to_vector(p_key);
//                updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, temp);

                p_key_file->update_key(p_key);

            } else if (columns_type_from_file[i]==TEXT) {

                string empty_str = string_utilities::format_string_for_uint8_t("''");
                vector<uint8_t> str_to_uint8_t_vector(empty_str.begin(), empty_str.end());
//                updated_record = string_utilities::append_vector_uint8t_into_another(updated_record, str_to_uint8_t_vector);

            }
        }

        vector_pair_is_modify_value.emplace_back(make_pair(is_column_in_update_query,temp));

    }

    if (is_where_clause_get()) {
        set_where_clause(build_where_clause::build_where(get_query(), UPDATE_SYNTAX, columns_name_from_file));
    }

}

void update_query::expand() {}

void update_query::execute() {

    content_file* content_file = content_file::get_instance();
    vector<vector<uint8_t>> vector_all_records = content_file->retrieve_all();

    index_file* index_file = index_file::get_instance();
    vector<index_entry> vector_all_indexes = index_file->retrieve_all();

    definition_file* definition_file = definition_file::get_instance();
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    vector<vector<uint8_t>> all_modified_record;
    vector<uint32_t> indexes_modified_record;

    if (!is_where_clause_get()) {

        for (int i = 0; i < vector_all_indexes.size(); ++i) {
            vector<uint8_t> modified_record;

            //test if is an active record
            if (vector_all_indexes.at(i).is_active) {
                indexes_modified_record.push_back(vector_all_indexes.at(i).position);
//                all_modified_record.push_back();
            }

        }

    } else {
        //for each record
        for (int i = 0; i < vector_all_indexes.size(); ++i) {


            //test if is an active record
            if (vector_all_indexes.at(i).is_active) {

                vector<uint8_t> record = vector_all_records.at(i);
                //TODO where management
                if (where_clause.is_where_clause_apply(record, columns_name_from_file)) {

                    vector<vector<uint8_t>> columns_record = string_utilities::split_vector_with_type_length(record, columns_type_from_file);

                    // modify only if it is a column in the query
                    for (int j = 0; j < vector_pair_is_modify_value.size(); ++j) {
                        if (vector_pair_is_modify_value.at(j).first) {
                            columns_record.at(j) = vector_pair_is_modify_value.at(j).second;
                        }
                    }

                    vector<uint8_t> modified_record = string_utilities::convert_vector_of_vector_uint8t_into_vector(columns_record);

                    all_modified_record.push_back(modified_record);
                    indexes_modified_record.push_back(vector_all_indexes.at(i).position);

                }

            }

        }

    } // end else clause where


    //Todo write records of all modified record into content file with index
    for (int i = 0; i < indexes_modified_record.size(); ++i) {
        content_file->write_record(all_modified_record.at(i),indexes_modified_record.at(i));
    }

}


bool update_query::is_where_clause_get() const {
    return is_where_clause;
}

void update_query::set_is_where_clause(bool isWhereClause) {
    is_where_clause = isWhereClause;
}

const where_clause &update_query::get_where_clause() const {
    return where_clause;
}

void update_query::set_where_clause(const class where_clause &whereClause) {
    where_clause = whereClause;
}
