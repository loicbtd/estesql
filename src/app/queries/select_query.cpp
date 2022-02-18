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

    // 3 memorize indexes of selected columns + test if all columns from query exist
    bool is_column_exist;
    vector<int> columns_selected_indexes_(columns_name_from_file.size(),0);
    for (int i = 0; i < columns_select_vector.size(); ++i) {

        is_column_exist = false;
        for (int j = 0; j < columns_name_from_file.size(); ++j) {

            if (columns_select_vector[i] == columns_name_from_file[j]) {
                is_column_exist = true;
                columns_selected_indexes_.at(j) = 1;
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
    vector<vector<uint8_t>> vector_all_records = content_file->retrieve_all();

    index_file* index_file = index_file::get_instance();
    vector<index_entry> vector_all_indexes = index_file->retrieve_all();

    definition_file* definition_file = definition_file::get_instance();
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    vector<vector<uint8_t>> records_to_display;


    for (int i = 0; i < vector_all_indexes.size(); ++i) {

        if (vector_all_indexes.at(i).is_active) {

            vector<uint8_t> record = vector_all_records.at(i);
            vector<vector<uint8_t>> columns_record = string_utilities::split_vector_with_type_length(record, columns_type_from_file);

            if (where_clause.is_where_clause_apply(columns_record, columns_name_from_file, columns_type_from_file)) {
                records_to_display.push_back(record);
            }

        }

    }

    int nb_columns_displayed = 0;
    vector<string> columns_names_displayed;
    for (int i = 0; i < columns_selected_indexes.size(); ++i) {
        if (columns_selected_indexes.at(i) == 1) {
            nb_columns_displayed = nb_columns_displayed + 1;
            columns_names_displayed.push_back(columns_name_from_file.at(i));
        }

    }

    // header
    draw_line(nb_columns_displayed);
    for (const auto& column_name_displayed: columns_names_displayed) {
        cout << "|" << setw(WIDTH_COLUMN-1) << column_name_displayed;
    }
    cout << "|" << endl;
    draw_line(nb_columns_displayed);
    // end header


    for (int i = 0; i < vector_all_records.size(); ++i) {
        vector<vector<uint8_t>> columns_record = string_utilities::split_vector_with_type_length(vector_all_records.at(i), columns_type_from_file);

        for (int j = 0; j < columns_selected_indexes.size(); ++j) {

            if (columns_selected_indexes.at(j) == 1) {
                cout << "|" << setw(WIDTH_COLUMN-1) << string_utilities::get_value_of_vector(columns_record.at(j), columns_type_from_file.at(j));
            }

        }
        cout << "|" << endl;

    }

    draw_line(nb_columns_displayed);

}

void select_query::draw_line(int nb_columns_displayed) {

    for (int i = 0; i <= nb_columns_displayed * WIDTH_COLUMN; ++i) {
        if ((i % WIDTH_COLUMN) == 0) {
            cout << "|";
        } else {
            cout << "-";
        }
    }

    cout << endl;

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
