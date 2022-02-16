#include "definition_file_should.h"

string definition_file_should::name() {
    return "definition_file_should";
}

map<string, bool> definition_file_should::pass_tests() {
    return {
            {"get_table_definition",       get_table_definition()},
            {"write_get_table_definition", write_get_table_definition()},
    };
}


bool definition_file_should::get_table_definition() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    definition_file *file = definition_file::get_instance();
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    vector<column_definition *> columns = file->get_table_definition().get_columns();

    // Assert
    return (
            columns.size() == 4 &&
            columns[0]->get_type() == PRIMARY_KEY &&
            columns[1]->get_type() == INT &&
            columns[2]->get_type() == FLOAT &&
            columns[3]->get_type() == TEXT &&
            strcmp(columns[0]->get_name().c_str(), "field1") == 0 &&
            strcmp(columns[1]->get_name().c_str(), "field2") == 0 &&
            strcmp(columns[2]->get_name().c_str(), "field3") == 0 &&
            strcmp(columns[3]->get_name().c_str(), "field4") == 0
    );
}

bool definition_file_should::write_get_table_definition() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    definition_file *file = definition_file::get_instance();
    file->set_current_table_name(to_string((time(nullptr))));

    table_definition definition = table_definition();

    column_definition *column1 = new column_definition();
    column1->set_type(PRIMARY_KEY);
    column1->set_name("field1");
    definition.add_column(column1);

    column_definition *column2 = new column_definition();
    column2->set_type(FLOAT);
    column2->set_name("field2");
    definition.add_column(column2);

    // Act
    file->write_table_definition(definition);

    // Assert
    vector<column_definition *> columns = file->get_table_definition().get_columns();
    return (
            columns.size() == 2 &&
            columns[0]->get_type() == PRIMARY_KEY &&
            columns[1]->get_type() == FLOAT &&
            strcmp(columns[0]->get_name().c_str(), "field1") == 0 &&
            strcmp(columns[1]->get_name().c_str(), "field2") == 0
    );
}
