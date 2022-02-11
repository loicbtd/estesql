#include "definition_file_should.h"

string definition_file_should::name() {
    return "definition_file_should";
}

map<string, bool> definition_file_should::pass_tests() {
    return {
            {"exist",                      exist()},
            {"not_exist",                  not_exist()},
            {"get_table_definition",       get_table_definition()},
            {"write_get_table_definition", write_get_table_definition()},
    };
}

bool definition_file_should::exist() {
    // Arrange
    db_info::GetInstance()->setCurrentDbPath(DATABASE1_PATH);
    definition_file *definition = new definition_file("table1");

    // Act
    // Assert
    return definition->exists();
}

bool definition_file_should::not_exist() {
    // Arrange
    db_info::GetInstance()->setCurrentDbPath(DATABASE1_PATH);
    definition_file *definition = new definition_file("lorem");

    // Act
    // Assert
    return !definition->exists();
}

bool definition_file_should::get_table_definition() {
    // Arrange
    db_info::GetInstance()->setCurrentDbPath(DATABASE1_PATH);
    definition_file *file = new definition_file("table1");

    // Act
    vector<column_definition *> columns = file->get_table_definition().getColumns();

    // Assert
    return (
            columns.size() == 4 &&
            columns[0]->getType() == PRIMARY_KEY &&
            columns[1]->getType() == INT &&
            columns[2]->getType() == FLOAT &&
            columns[3]->getType() == TEXT &&
            strcmp(columns[0]->getName().c_str(), "field1") == 0 &&
            strcmp(columns[1]->getName().c_str(), "field2") == 0 &&
            strcmp(columns[2]->getName().c_str(), "field3") == 0 &&
            strcmp(columns[3]->getName().c_str(), "field4") == 0
    );
}

bool definition_file_should::write_get_table_definition() {
    // Arrange
    db_info::GetInstance()->setCurrentDbPath(DATABASE1_PATH);
    definition_file *file = new definition_file(to_string((time(nullptr))));

    table_definition definition = table_definition();

    column_definition* column1 = new column_definition();
    column1->setType(PRIMARY_KEY);
    column1->setName("field1");
    definition.addColumn(column1);

    column_definition* column2 = new column_definition();
    column2->setType(FLOAT);
    column2->setName("field2");
    definition.addColumn(column2);

    // Act
    file->write_table_definition(definition);

    // Assert
    vector<column_definition *> columns = file->get_table_definition().getColumns();
    return (
            columns.size() == 2 &&
            columns[0]->getType() == PRIMARY_KEY &&
            columns[1]->getType() == FLOAT &&
            strcmp(columns[0]->getName().c_str(), "field1") == 0 &&
            strcmp(columns[1]->getName().c_str(), "field2") == 0
    );
}