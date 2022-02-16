#include "index_file_should.h"

string index_file_should::name() {
    return "index_file_should";
}

map<string, bool> index_file_should::pass_tests() {
    return {
            {"write_and_retrieve_the_same", write_and_retrieve_the_same()},
    };
}

bool index_file_should::write_and_retrieve_the_same() {
    // Arrange
    db_info* info = db_info::get_instance();
    info->set_current_db_path(TEST_CURRENT_DB_PATH);
    info->set_db_name(TEST_DB_NAME);
    info->set_db_parent_folder_path(TEST_DB_PARENT_FOLDER_PATH);

    index_file *file = index_file::get_instance();
    file->set_current_table_name(to_string((time(nullptr))));

    index_entry initial_entry0 = index_entry();
    initial_entry0.is_active = false;
    initial_entry0.position = 65;
    initial_entry0.length = 254;

    index_entry initial_entry1 = index_entry();
    initial_entry1.is_active = true;
    initial_entry1.position = 5954;
    initial_entry1.length = 41;

    index_entry initial_entry2 = index_entry();
    initial_entry2.is_active = true;
    initial_entry2.position = 1551994;
    initial_entry2.length = 8118;

    // Act
    file->write_index_entry(initial_entry0, 0);
    file->write_index_entry(initial_entry1, 1);
    file->write_index_entry(initial_entry2, 2);

    index_entry final_entry0 = file->get_index_entry(0);
    index_entry final_entry1 = file->get_index_entry(1);
    index_entry final_entry2 = file->get_index_entry(2);

    // Assert
    return (
            initial_entry0.is_active == final_entry0.is_active &&
            initial_entry0.position == final_entry0.position &&
            initial_entry0.length == final_entry0.length &&
            initial_entry1.is_active == final_entry1.is_active &&
            initial_entry1.position == final_entry1.position &&
            initial_entry1.length == final_entry1.length &&
            initial_entry2.is_active == final_entry2.is_active &&
            initial_entry2.position == final_entry2.position &&
            initial_entry2.length == final_entry2.length
    );
}
