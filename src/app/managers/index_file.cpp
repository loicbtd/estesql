#include "index_file.h"

index_file* index_file::index_file_ = nullptr;

index_file *index_file::get_instance() {
    if (index_file_ == nullptr) {
        index_file_ = new index_file();
    }

    return index_file_;
}

void index_file::write_index_entry(const index_entry &entry, uint32_t offset) {
    open();

    if (get_size() < ((offset) * sizeof(index_entry))) {
        throw inability_to_write_after_undefined_index_file_position_exception();
    }

    file.seekp(56 * offset);

    file << bitset<INDEX_ENTRY_PERSISTED_IS_ACTIVE_SIZE_IN_BITS>(entry.is_active ? "0" : "1")
         << bitset<INDEX_ENTRY_PERSISTED_POSITION_SIZE_IN_BITS>(entry.position)
         << bitset<INDEX_ENTRY_PERSISTED_LENGTH_SIZE_IN_BITS>(entry.length);

    close();
}


index_entry index_file::get_index_entry(uint32_t position) {
    open();

    if (get_size() < ((position + 1) * sizeof(index_entry))) {
        throw inability_to_read_undefined_index_file_position_exception();
    }

    file.seekg(position * INDEX_ENTRY_PERSISTED_SIZE_IN_BITS);

    char is_active_data[INDEX_ENTRY_PERSISTED_IS_ACTIVE_SIZE_IN_BITS];
    file.read(is_active_data, INDEX_ENTRY_PERSISTED_IS_ACTIVE_SIZE_IN_BITS);
    string is_active_binary_string = "00000000000000000000000000" + (string) is_active_data;

    char position_data[INDEX_ENTRY_PERSISTED_POSITION_SIZE_IN_BITS];
    file.read(position_data, INDEX_ENTRY_PERSISTED_POSITION_SIZE_IN_BITS);
    string position_binary_string = (string) position_data;

    char length_data[INDEX_ENTRY_PERSISTED_LENGTH_SIZE_IN_BITS];
    file.read(length_data, INDEX_ENTRY_PERSISTED_LENGTH_SIZE_IN_BITS);
    string length_binary_string = "0000000000000000" + (string) length_data;

    index_entry entry = index_entry();
    entry.is_active = stoi(is_active_binary_string, nullptr, 2) == 0;
    entry.position = stoi(position_binary_string, nullptr, 2);
    entry.length = stoi(length_binary_string, nullptr, 2);

    close();

    return entry;
}

int index_file::get_entries_count() {
    open();
    close();
    return get_size() / INDEX_ENTRY_PERSISTED_SIZE_IN_BITS;
}

uint32_t index_file::get_first_inactive_index() {
    for (uint32_t position = 0; position < get_entries_count(); ++position) {
        if(!get_index_entry(position).is_active) {
           return position;
        }
    }

    return get_entries_count();
}

vector<index_entry> index_file::retrieve_all() {

    uintmax_t size = get_entries_count();
    vector<index_entry> entries;
    for (int position = 0; position < size; ++position) {
        entries.push_back(get_index_entry(position));
    }

    return entries;
}


