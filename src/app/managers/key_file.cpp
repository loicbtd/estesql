#include "key_file.h"

key_file *key_file::key_file_ = nullptr;;

key_file *key_file::get_instance() {
    if (key_file_ == nullptr) {
        key_file_ = new key_file();
    }

    return key_file_;
}

uint64_t key_file::get_next_key() {
    return 0;
}

void key_file::update_key(uint64_t last_value) {

}
