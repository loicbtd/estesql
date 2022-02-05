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
    db_info *dbInfo;
    try {
        dbInfo = db_info::GetInstance();
        dbInfo->setCurrentDbPath(DATABASE1_PATH);
    } catch (exception &) {
        return false;
    }

    definition_file *file;
    try {
        file = new definition_file("database1");
    } catch (exception &) {
        return false;
    }

    // Act
    vector<column_definition *> columns;
    try {
        columns = file->get_table_definition().getColumns();
    } catch (exception &) {
        return false;
    }

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
    return false;
}
