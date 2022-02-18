#include "content_file.h"

content_file *content_file::content_file_ = nullptr;;

content_file *content_file::get_instance() {
    if (content_file_ == nullptr) {
        content_file_ = new content_file();
    }

    return content_file_;
}

void content_file::write_record(const vector <uint8_t> &record, uint32_t offset) {
    open();

    file.seekp((int) record.size() * offset);

    file << string(record.begin(), record.end());

    close();

    index_entry entry = index_entry();
    entry.is_active = true;
    entry.length = record.size();
    entry.position = offset;

    index_file::get_instance()->write_index_entry(entry, offset);
}

vector <uint8_t> content_file::read_record(uint16_t length, uint32_t offset) {
    open();

    file.seekg(offset * length);

    char data_buffer[length];
    file.read(data_buffer, length);
    string data_string(data_buffer);

    close();

    return vector<uint8_t>(data_string.begin(), data_string.end());
}

vector <vector<uint8_t>> content_file::retrieve_all() {
//    open();

    vector <vector<uint8_t>> contents;
    string line_buffer;
    vector <uint8_t> temporary_content;

    uint16_t record_length = definition_file::get_instance()->get_record_length();
    int entries_count = get_entries_count();

    file.seekg(0);
    for (int offset = 0; offset < entries_count; ++offset) {
        contents.push_back(read_record(record_length, offset));
    }

//    close();

    return contents;
}

int content_file::get_entries_count() {
    open();
    close();
    return get_size() / definition_file::get_instance()->get_record_length();
}

