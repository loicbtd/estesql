#include "content_file.h"

content_file *content_file::content_file_ = nullptr;;

content_file *content_file::get_instance() {
    if (content_file_ == nullptr) {
        content_file_ = new content_file();
    }

    return content_file_;
}

void content_file::write_record(const vector<uint8_t> &record, uint32_t offset) {

}

vector<uint8_t> content_file::read_record(uint32_t offset) {
    return vector<uint8_t>();
}

