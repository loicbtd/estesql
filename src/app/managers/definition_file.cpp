#include "definition_file.h"

definition_file *definition_file::definition_file_ = nullptr;;

definition_file *definition_file::get_instance() {
    if (definition_file_ == nullptr) {
        definition_file_ = new definition_file();
    }

    return definition_file_;
}

table_definition definition_file::get_table_definition() {
    open();

    string line;

    table_definition table = table_definition();

    column_definition *column;

    while (getline(this->file, line)) {
        column = new column_definition();
        column->set_type(field_type_t(stoi(line.substr(0, line.find(' ')))));
        column->set_name(line.substr(line.find(' ') + 1, line.length() - 1));
        table.add_column(column);
    }

    close();

    return table;
}

vector<string> definition_file::get_all_columns_names() {

    vector<string> columns_name_from_file;

    for (auto col_def: get_table_definition().get_columns()) {
        columns_name_from_file.push_back(col_def->get_name());
    }

    return columns_name_from_file;

}

vector<field_type_t> definition_file::get_all_columns_types() {

    vector<field_type_t> columns_types_from_file;

    for (auto col_def: get_table_definition().get_columns()) {
        columns_types_from_file.push_back(col_def->get_type());
    }

    return columns_types_from_file;

}

void definition_file::write_table_definition(const table_definition &definition) {
    open();

    for (column_definition *column: definition.get_columns()) {
        file << column->get_type() << " " << column->get_name() << endl;
    }

    close();
}


