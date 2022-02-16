#include "create_table_query.h"

void create_table_query::parse() {

    string str_regex ("create table ");
    str_regex.append(get_table_name()).append(" \\\([a-z0-9_-]+ (int|primary_key|float|text)(,( )?[a-z0-9_-]+ (int|primary_key|float|text)( )?)*\\\)( )?;");

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
    }

}

void create_table_query::check() {

    parse();

    definition_file* def_file = definition_file::get_instance();

    if (def_file->exists()) {
        throw already_existing_table_exception();
    }

    smatch smatch_;
    string columns = "\\\([a-z0-9_-]+ (int|primary_key|float|text)(,( )?[a-z0-9_-]+ (int|primary_key|float|text)( )?)*\\\)";
    string parameters_str;
    if (regex_search(get_query(), smatch_, regex(columns))) {
        parameters_str = smatch_.str();
    }

    parameters_str.erase(remove(parameters_str.begin(), parameters_str.end(), PARENTHESIS_OPEN_DELIMITER), parameters_str.end());
    parameters_str.erase(remove(parameters_str.begin(), parameters_str.end(), PARENTHESIS_CLOSE_DELIMITER), parameters_str.end());

    stringstream str_stream(parameters_str);
    vector<column_definition*> columns_vector;

    int count_primary_key(0);

    while(str_stream.good()) {

        string substr;
        getline(str_stream, substr, COMA_DELIMITER);

        string trim_str(string_utilities::trim(substr));

        stringstream str_stream_space(trim_str);
        istream_iterator<string> begin(str_stream_space);
        istream_iterator<string> end;
        vector<string> names_types_str_vector(begin, end);

        column_definition* column = new column_definition();
        column->set_name(names_types_str_vector[0]);

        if (names_types_str_vector[1]==enum_field_type_str[0]) {
            column->set_type(INT);
        } else if (names_types_str_vector[1]==enum_field_type_str[1]) {
            column->set_type(FLOAT);
        } else if (names_types_str_vector[1]==enum_field_type_str[2]) {
            column->set_type(TEXT);
        } else if (names_types_str_vector[1]==enum_field_type_str[3]) {
            column->set_type(PRIMARY_KEY);
            count_primary_key++;
        }

        columns_vector.push_back(column);
    }

    if (db_table_utilities::is_duplicate_columns(columns_vector)) {
        throw insert_duplicate_columns_exception();
    }

    if (count_primary_key != 1) {
        throw missing_or_multiple_primary_key_exception();
    }

    set_table_definition_create(table_definition(columns_vector));

}

void create_table_query::expand() {}

void create_table_query::execute() {

    definition_file::get_instance()->write_table_definition(get_table_definition_create());

}

const table_definition &create_table_query::get_table_definition_create() const {
    return table_definition_create;
}

void create_table_query::set_table_definition_create(const table_definition &tableDefinitionCreate) {
    table_definition_create = tableDefinitionCreate;
}

