#include "create_table_query.h"

void create_table_query::parse() {

    string str_regex ("create table ");
    str_regex.append(getTableName()).append(" \\\([a-z0-9_-]+ (int|primary_key|float|text)(,( )?[a-z0-9_-]+ (int|primary_key|float|text)( )?)*\\\)( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_TABLE_SYNTAX);
    }

}

void create_table_query::check() {

    parse();
    //Todo 1 getInstance of definition_file
    //Todo 2 check if table exists ie if diectory with name of the table exists

    bool temp_bool_table_exists = false;

    if (temp_bool_table_exists) {
        throw already_existing_table_exception();
    }

    smatch smatch_;
    string columns = "\\\([a-z0-9_-]+ (int|primary_key|float|text)(,( )?[a-z0-9_-]+ (int|primary_key|float|text)( )?)*\\\)";
    string parameters_str;
    if (regex_search(getQuery(), smatch_, regex(columns))) {
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
        column->setName(names_types_str_vector[0]);

        if (names_types_str_vector[1]==enum_field_type_str[0]) {
            column->setType(INT);
        } else if (names_types_str_vector[1]==enum_field_type_str[1]) {
            column->setType(FLOAT);
        } else if (names_types_str_vector[1]==enum_field_type_str[2]) {
            column->setType(TEXT);
        } else if (names_types_str_vector[1]==enum_field_type_str[3]) {
            column->setType(PRIMARY_KEY);
            count_primary_key++;
        }

        columns_vector.push_back(column);
    }

    if (count_primary_key != 1) {
        throw missing_or_multiple_primary_key_exception();
    }

    //TODO 1 getInstance of table_definition
    //TODO 2 setColumnVector

}

void create_table_query::expand() {}

void create_table_query::execute() {

    //Todo 1 getInstance of table_definition
    //Todo 2 getInstance of definition_file
    //Todo 3 definition_file_instance->write_table_definition(table_definition);

}

