#include "content_file.h"

content_file *content_file::content_file_ = nullptr;;

content_file *content_file::get_instance() {
    if (content_file_ == nullptr) {
        content_file_ = new content_file();
    }

    return content_file_;
}

void content_file::write_record(const vector<uint8_t> &record, uint32_t offset) {
    open();

    file.seekg(offset, ios::end);

    uint8_t cursor = 1;

    for (uint8_t record_item: record) {
        file << record_item;
        file.seekp(offset + cursor, ios::beg);
        cursor++;
    }

    close();
}

vector<uint8_t> content_file::read_record(uint16_t length, uint32_t offset) {
    open();

    vector<uint8_t> data(istreambuf_iterator<char>(file), {});

    close();

    return {data.begin() + offset, data.begin() + offset + length};
}

