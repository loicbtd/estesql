#include "table_file_should.h"

string table_file_should::name() {
    return "table_file_should";
}

map<string, bool> table_file_should::pass_tests() {
    return {
            {"exist",     exist()},
            {"not_exist", not_exist()},
            {"open",      open()},
            {"close",     close()},
            {"not_close",  not_close()},
    };
}

bool table_file_should::exist() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file(DEFINITION_FILE_EXTENSION);
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    // Assert
    return file->exists();
}

bool table_file_should::not_exist() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file("");
    file->set_current_table_name(to_string((time(nullptr))));

    // Act
    // Assert
    return !file->exists();
}

bool table_file_should::open() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file(DEFINITION_FILE_EXTENSION);
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    try {
        file->open();
    } catch (exception &) {
        return false;
    }

    // Assert
    return true;
}

bool table_file_should::close() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file(DEFINITION_FILE_EXTENSION);
    file->set_current_table_name(TEST_TABLE_NAME);

    // Act
    try {
        file->open();
        file->close();
    } catch (exception &) {
        return false;
    }

    // Assert
    return true;
}

bool table_file_should::not_close() {
    // Arrange
    db_info *info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    table_file *file = new table_file(DEFINITION_FILE_EXTENSION);
    file->set_current_table_name(to_string((time(nullptr))));

    // Act
    try {
        file->close();
    } catch (exception &) {
        return true;
    }

    // Assert
    return false;
}