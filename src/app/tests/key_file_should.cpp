#include "key_file_should.h"

string key_file_should::name() {
    return "key_file_should";
}

map<string, bool> key_file_should::pass_tests() {
    return {
            {"get_next_key", get_next_key()},
            {"update_key", update_key()},
    };
}

bool key_file_should::get_next_key() {
    return false;
}

bool key_file_should::update_key() {
    return false;
}



