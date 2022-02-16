#include "index_file_should.h"

string index_file_should::name() {
    return "index_file_should";
}

map<string, bool> index_file_should::pass_tests() {
    return {
            {"get_index_entry",       get_index_entry()},
            {"write_index_entry", write_index_entry()},
    };
}

bool index_file_should::get_index_entry() {
    // Arrange
    db_info* info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    index_file *file = index_file::get_instance();
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    index_entry entry;

    try {
        entry = file->get_index_entry(0);
    } catch (exception &) {
        return false;
    }

    // Assert
    return true;
}

bool index_file_should::write_index_entry() {
    return false;
//    // Arrange
//    db_info::get_instance()->set_current_db_path(DATABASE1_PATH);
//    index_file *file = new index_file(to_string((time(nullptr))));
//
//    table_definition definition = table_definition();
//
//    column_definition* column1 = new column_definition();
//    column1->set_type(PRIMARY_KEY);
//    column1->setName("field1");
//    definition.addColumn(column1);
//
//    column_definition* column2 = new column_definition();
//    column2->set_type(FLOAT);
//    column2->setName("field2");
//    definition.addColumn(column2);
//
//    // Act
//    file->write_table_definition(definition);
//
//    // Assert
//    vector<column_definition *> columns = file->get_table_definition().getColumns();
//    return (
//            columns.size() == 2 &&
//            columns[0]->get_type() == PRIMARY_KEY &&
//            columns[1]->get_type() == FLOAT &&
//            strcmp(columns[0]->getName().c_str(), "field1") == 0 &&
//            strcmp(columns[1]->getName().c_str(), "field2") == 0
//    );
}
