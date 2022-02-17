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


    if (is_where_clause_get()) {
        set_where_clause(build_where_clause::build_where(get_query(), UPDATE_SYNTAX, columns_name_from_file));
    }

}

void update_query::expand() {}

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
