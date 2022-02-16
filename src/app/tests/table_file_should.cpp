#include "table_file_should.h"

string table_file_should::name() {
    return "table_file_should";
}

map<string, bool> table_file_should::pass_tests() {
    return {
            {"exist",     exist()},
            {"not_exist", not_exist()},
            {"open",      open()},
            {"not_open",  not_open()},
            {"close",     close()},
            {"not_open",  not_open()},
    };
}

bool table_file_should::exist() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->setCurrentDbPath(TEST_CURRENT_DB_PATH);
    info->setDbName(TEST_DB_NAME);
    info->setDbParentFolderPath(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file("");
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    // Assert
    return file->exists();
}

bool table_file_should::not_exist() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->setCurrentDbPath(TEST_CURRENT_DB_PATH);
    info->setDbName(TEST_DB_NAME);
    info->setDbParentFolderPath(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file("");
    file->set_current_table_name(to_string((time(nullptr))));

    // Act
    // Assert
    return !file->exists();
}

bool table_file_should::open() {
    // Arrange
    // Act
    // Assert
    return false;
}

bool table_file_should::not_open() {
    // Arrange
    // Act
    // Assert
    return false;
}

bool table_file_should::close() {
    // Arrange
    // Act
    // Assert
    return false;
}

bool table_file_should::not_close() {
    // Arrange
    // Act
    // Assert
    return false;
}