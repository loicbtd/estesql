#include "definition_file.h"

table_definition definition_file::get_table_definition() {
    open();

    string line;

    table_definition tableDefinition = table_definition();

    column_definition* column;

    while (getline(this->file, line)) {
        column = new column_definition();
        column->setType(field_type_t(stoi(line.substr(0, line.find(' ')))));
        column->setName(line.substr(line.find(' ') +1 , line.length() -1));
        tableDefinition.addColumn(column);
    }

    close();

    return tableDefinition;
}

void definition_file::write_table_definition(const table_definition &definition) {


}

bool definition_file::exists() {
    return filesystem::exists(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::open() {
    if (!exists()) {
        throw file_doest_not_exist_exception();
    }
    file.open(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::close() {
    if (!file.is_open()) {
        throw file_is_not_open_exception();
    }
    file.close();
}
