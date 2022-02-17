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

    index_entry entry = index_entry();
    entry.is_active = true;
    entry.length = record.size();
    entry.position = offset;

    index_file::get_instance()->write_index_entry(entry, offset);

    file.seekp(0);
    string line_buffer;
    for (long long counter = 0; counter < offset; ++counter) {
        getline(file, line_buffer);
    }

    for (uint8_t record_item: record) {
        file << record_item;
    }
    file << endl;

    close();
}

vector<uint8_t> content_file::read_record(uint16_t length, uint32_t offset) {
    open();

    vector<uint8_t> data(istreambuf_iterator<char>(file), {});

    close();

    return {data.begin() + offset, data.begin() + offset + length};
}

vector<vector<uint8_t>> content_file::retrieve_all() {
    return vector<vector<uint8_t>>();
}

