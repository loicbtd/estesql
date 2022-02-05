#include "definition_file.h"

table_definition definition_file::get_table_definition() {
    return table_definition();
}

void definition_file::write_table_definition(const table_definition &definition) {

}

bool definition_file::exists() {
    return filesystem::exists(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::open() {
    close();
    if (!exists()) {
        throw file_doest_not_exist_exception();
    }
    file.open(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::close() {
    if (!file.is_open()) {
        throw file_is_not_open_exception();
    }
    file.close();
}
