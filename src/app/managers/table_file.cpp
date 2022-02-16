#include "table_file.h"

table_file::table_file(string extension) {
    this->file_extension = extension;
}

const string &table_file::get_current_table_name() const {
    return source_file;
}

void table_file::set_current_table_name(const string &source) {
    this->source_file = source;
}

bool table_file::exists() {
    bool exist;

    try {
        exist = filesystem::exists(
                db_info::get_instance()->getCurrentDbPath() + "/" + source_file + "/" + source_file + file_extension);
    } catch (exception &) {
        throw inability_to_check_if_file_exists_exception();
    }

    return exist;
}

void table_file::open() {
    if (!exists()) {
        try {
            filesystem::create_directories(db_info::get_instance()->getCurrentDbPath() + "/" + source_file);
        } catch (exception &) {
            throw inability_to_create_directory_exception();
        }

        try {
            auto a= fopen((db_info::get_instance()->getCurrentDbPath() + "/" + source_file + "/" + source_file +
                   file_extension).c_str(), "w+");

            fclose(a);
        } catch (exception &) {
            throw inability_to_create_file_exception();
        }
    }

    try {
        file.open(db_info::get_instance()->getCurrentDbPath() + "/" + source_file + "/" + source_file + file_extension);
    }
    catch (exception &) {
        throw inability_to_open_file_exception();
    }
}

void table_file::close() {
    if (!file.is_open()) {
        throw file_is_not_open_exception();
    }
    file.close();
}
