#include "index_file.h"

void index_file::write_index_entry(const index_entry &entry, uint32_t offset) {

}


index_entry index_file::get_index_entry(uint32_t position) {
    return index_entry();
}


bool index_file::exists() {
    return filesystem::exists(
            db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".idx");
}

void index_file::open() {
    if (!exists()) {
        filesystem::create_directories(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/");
        fopen((db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file +
               ".idx").c_str(), "w+");
    }

    file.open(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".idx");
}

void index_file::close() {
    if (!file.is_open()) {
        throw file_is_not_open_exception();
    }
    file.close();
}
