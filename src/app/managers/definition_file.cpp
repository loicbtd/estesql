#include "definition_file.h"

table_definition definition_file::get_table_definition() {
    open();

    string line;

    table_definition tableDefinition = table_definition();

    column_definition *column;

    while (getline(this->file, line)) {
        column = new column_definition();
        column->setType(field_type_t(stoi(line.substr(0, line.find(' ')))));
        column->setName(line.substr(line.find(' ') + 1, line.length() - 1));
        tableDefinition.addColumn(column);
    }

    close();

    return tableDefinition;
}

void definition_file::write_table_definition(const table_definition &definition) {
    open();

    for (column_definition *column: definition.getColumns()) {
        file << column->getType() << " " << column->getName() << endl;
    }

    close();
}

bool definition_file::exists() {
    return filesystem::exists(
            db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::open() {
    if (!exists()) {
        filesystem::create_directories(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/");
        fopen((db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file +
               ".def").c_str(), "w+");
    }

    file.open(db_info::GetInstance()->getCurrentDbPath() + "/" + this->source_file + "/" + this->source_file + ".def");
}

void definition_file::close() {
    if (!file.is_open()) {
        throw file_is_not_open_exception();
    }
    file.close();
}
