#include "index_file.h"

index_file *index_file::index_file_ = nullptr;;

index_file *index_file::get_instance() {
    if (index_file_ == nullptr) {
        index_file_ = new index_file();
    }

    return index_file_;
}

void index_file::open() {
    table_file::open();

    uintmax_t size;
    try {
        size = filesystem::file_size(
                db_info::get_instance()->getCurrentDbPath() + "/" + source_file + "/" + source_file + file_extension);
    } catch (exception &) {
        throw inability_to_retrieve_file_length_exception();
    }

    if ((size % 7) != 0) {
        throw index_file_is_not_valid_exception();
    }
}

void index_file::write_index_entry(const index_entry &entry, uint32_t offset) {
    open();


    close();
}

index_entry index_file::get_index_entry(uint32_t position) {
    open();

    ifstream::pos_type position_in_file = file.tellg();

    if (position == 0) {
        return index_entry();
    }

    vector<char> result(position_in_file);

    file.seekg(0, ios::beg);
    file.read(&result[0], position_in_file);

    close();
    return index_entry();



//    size_t size = 0;
//    char *data = 0;
//
//    file.seekg(0, ios::end);
//    size = file.tellg();
//
//    file.seekg(0, ios::beg);
//
//    data = new char[size + 1];
//    file.read(data, size);
//    data[size]= '\0';
//
//    for(size_t counter = 0; counter < strlen(data); counter++) {
//
//    }

    close();

    return index_entry();
}


