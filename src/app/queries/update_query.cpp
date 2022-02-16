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

    //Todo 2.2 retrieve all columns from definition_file
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    //Todo check if all columns are in the table
    for(auto a : columns_values_vector) {
        cout << "pair(" << a.first << "," << a.second << ")" << endl;
    }

    bool is_column_in_insert_query;
    for (int i = 0; i < columns_name_from_file.size(); ++i) {

        is_column_in_insert_query = false;

        for (int j = 0; j < columns_values_vector.size(); ++j) {

            if (columns_values_vector.at(j).first==columns_name_from_file[i]) {

                is_column_in_insert_query = true;

                string value = columns_values_vector.at(j).second;

                if (
                        (string_utilities::contains(value,"'") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==FLOAT || columns_type_from_file[i]==PRIMARY_KEY))
                        || (string_utilities::contains(value,".") && (columns_type_from_file[i]==INT || columns_type_from_file[i]==PRIMARY_KEY || ((columns_type_from_file[i]!=TEXT && !string_utilities::contains(value,"'")))))
                        ) {
                    throw wrong_type_exception();
                }

                if (columns_type_from_file[i]==INT) {

                    updated_record.push_back(stoll(value));

                } else if (columns_type_from_file[i]==FLOAT) {

                    updated_record.push_back(stod(value));

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    throw update_primary_key_exception();

                } else if (columns_type_from_file[i]==TEXT) {

                    value = string_utilities::format_string_for_uint8_t(value);
                    vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
                    updated_record.insert(str_to_uint8_t_vector.end(), str_to_uint8_t_vector.begin(), str_to_uint8_t_vector.end());

                }

                break;
            }

            if (!is_column_in_insert_query) {

                if ((columns_type_from_file[i]==INT) || (columns_type_from_file[i]==FLOAT)) {

                    updated_record.push_back('\0');

                } else if (columns_type_from_file[i]==PRIMARY_KEY) {

                    key_file* p_key_file = key_file::get_instance();
                    uint64_t p_key(p_key_file->get_next_key());

                    p_key_file->update_key(p_key);

                    updated_record.push_back(p_key);

                } else if (columns_type_from_file[i]==TEXT) {

                    string empty_str = string_utilities::format_string_for_uint8_t("''");
                    vector<uint8_t> str_to_uint8_t_vector(empty_str.begin(), empty_str.end());
                    updated_record.insert(str_to_uint8_t_vector.end(), str_to_uint8_t_vector.begin(), str_to_uint8_t_vector.end());

                }
            }

        }



    if (is_where_clause_get()) {
        set_where_clause(build_where_clause::build_where(get_query(), UPDATE_SYNTAX, columns_name_from_file));
    }

}

void update_query::expand() {

}

void update_query::execute() {

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
