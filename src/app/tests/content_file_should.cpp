#include "content_file_should.h"

string content_file_should::name() {
    return "content_file_should";
}

map<string, bool> content_file_should::pass_tests() {
    return {
            {"write_record", write_record()},
            {"read_record", read_record()},
    };
}

bool content_file_should::write_record() {
    return false;
}

bool content_file_should::read_record() {
    return false;
}
