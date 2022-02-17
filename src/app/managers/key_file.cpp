#include "key_file.h"

key_file *key_file::key_file_ = nullptr;;

key_file *key_file::get_instance() {
    if (key_file_ == nullptr) {
        key_file_ = new key_file();
    }

    return key_file_;
}

uint64_t key_file::get_next_key() {
    if(!exists()) {
        update_key(0);
        return 1;
    }

    open();

    file.seekg(0);

    char key_data[UNSIGNED_LONG_LONG_SIZE_IN_BITS];
    file.read(key_data, UNSIGNED_LONG_LONG_SIZE_IN_BITS);
    string key_binary_string = (string) key_data;

    close();

    return stoi(key_binary_string, nullptr, 2);
}

void key_file::update_key(uint64_t last_value) {
    open();

    ++last_value;

    file.seekp(0);

    file << bitset<UNSIGNED_LONG_LONG_SIZE_IN_BITS>(last_value);

    close();
}
