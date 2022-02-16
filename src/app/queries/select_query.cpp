#include "select_query.h"

void select_query::parse() {

    string all_columns("select * from ");

    if (get_query().find(all_columns) != string::npos) {
        expand();
    }

    string str_regex ("select [a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)* from ");
    str_regex.append(get_table_name());

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
        throw slq_invalid_syntax_exception(SELECT_SYNTAX);
    }

}

void select_query::check() {

    parse();

    definition_file* definition_file = definition_file::get_instance();

    if (!definition_file->exists()) {
        throw non_existing_table_exception();
    }
    
    // 1 retrieve all columns from query
    smatch smatch_;
    string columns = "select [a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)* from ";
    regex_search(get_query(), smatch_, regex(columns));
    string columns_str = smatch_.str();

    columns_str = string_utilities::erase_substring(columns_str, "select ");
    columns_str = string_utilities::erase_substring(columns_str, " from ");

    vector<string> columns_select_vector = string_utilities::convert_string_to_vector_delimiter(columns_str, COMA_DELIMITER);

    // 2.2 retrieve all columns from definition_file
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    // 2.2 check if nb columns query <= nb columns file
    if (columns_select_vector.size() > columns_name_from_file.size()) {
        throw select_number_columns_exception();
    }

    // 3 memorize indexes of selected columns + test if all columns from query exist + set offset for reading
    bool is_column_exist;
    offset = 0;
    vector<int> columns_selected_indexes_(columns_name_from_file.size(),0);
    for (int i = 0; i < columns_name_from_file.size(); ++i) {

        if (columns_type_from_file[i] == INT || columns_type_from_file[i] == FLOAT || columns_type_from_file[i] == PRIMARY_KEY) {
            offset += 8;
        } else {
            offset += 255;
        }

        is_column_exist = false;
        for (int j = 0; j < columns_select_vector.size(); ++j) {

            if (columns_select_vector[j] == columns_name_from_file[i]) {
                is_column_exist = true;
                columns_selected_indexes_.at(i) = 1;
                break;
            }

        }

        if (!is_column_exist) {
            throw column_non_existing_exception();
        }

    }

    //clear vector
    columns_selected_indexes.clear();
    //copy * in attribute
    copy(columns_selected_indexes_.begin(), columns_selected_indexes_.end(), back_inserter(columns_selected_indexes));

    if (is_where_clause_get()) {
        set_where_clause(build_where_clause::build_where(get_query(), SELECT_SYNTAX, columns_name_from_file));
    }


}

void select_query::expand() {
// retrieve all columns from the tableName and replace '*' by them seprated by ','

    vector<string> columns_name_from_file = definition_file::get_instance()->get_all_columns_names();

    string replace = string_utilities::convert_vector_into_string_delimiter(columns_name_from_file, COMA_DELIMITER);

    string str_regex = "\\\*";
    string query_ = regex_replace(get_query(), regex(str_regex), replace);
//    cout << "query: " << query_<< endl;

    set_query(query_);

}

void select_query::execute() {

    content_file* content_file = content_file::get_instance();
    index_file* index_file = index_file::get_instance();

    //Todo retrieve all ative records
    vector<vector<uint8_t>> all_records;
    for (int i = 0; i < index_file->get_entries_count(); ++i) {
        index_entry entry = index_file->get_index_entry(i);
        if (entry.is_active) {
            all_records.push_back(content_file->read_record(entry.position));
        }
    }


    vector<string> columns_name_from_file = definition_file::get_instance()->get_all_columns_names();

    for (int i = 0; i < columns_name_from_file.size(); ++i) {
        if (columns_selected_indexes[i]==1) {
            //Todo put all values of this column into structure => need to be determined
            //Todo where clause management /!\

            pair<string, vector<string>> where_element;
            for (const auto & element : get_where_clause().get_elements()){
//            cout << element.first.c_str() << " | " << element.second.at(0) << endl;
                if (std::find(columns_name_from_file.begin(), columns_name_from_file.end(), element.second.at(0)) != columns_name_from_file.end()) {
                    where_element = element;
                    break;
                }
            }

        }
    }

}



const vector<int> &select_query::get_columns_selected_indexes() const {
    return columns_selected_indexes;
}

void select_query::set_columns_selected_indexes(const vector<int> &columnsSelectedIndexes) {
    columns_selected_indexes = columnsSelectedIndexes;
}

uint32_t select_query::get_offset() const {
    return offset;
}

void select_query::set_offset(uint32_t offset) {
    select_query::offset = offset;
}

bool select_query::is_where_clause_get() const {
    return is_where_clause;
}

void select_query::set_is_where_clause(bool isWhereClause) {
    is_where_clause = isWhereClause;
}

const where_clause &select_query::get_where_clause() const {
    return where_clause;
}

void select_query::set_where_clause(const class where_clause &whereClause) {
    where_clause = whereClause;
}
