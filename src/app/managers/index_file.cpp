#include "index_file.h"

index_file* index_file::index_file_= nullptr;;

index_file *index_file::get_instance() {
    if (index_file_ == nullptr) {
        index_file_ = new index_file();
    }

    return index_file_;
}

void index_file::write_index_entry(const index_entry &entry, uint32_t offset) {

}

index_entry index_file::get_index_entry(uint32_t position) {
    return index_entry();
}
