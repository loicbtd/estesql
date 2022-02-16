#include "create_database_query.h"

void create_database_query::parse() {

    string str_regex ("create (database|db) ");
    str_regex.append(get_db_name()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_DB_SYNTAX);
    }

}

void create_database_query::check() {

    parse();

    string parent_folder_path = db_info::get_instance()->get_db_parent_folder_path();

    if (db_table_utilities::exists(parent_folder_path.append("/").append(get_db_name()).c_str())) {
        throw already_existing_db_exception();
    }

}

void create_database_query::expand() {}

void create_database_query::execute() {

    string parent_folder_path = db_info::get_instance()->get_db_parent_folder_path();
    create_db_at_path(parent_folder_path.append("/").append(get_db_name()));

}

void create_database_query::create_db_at_path(string db_path_name) {
    fs::create_directory(db_path_name);
    cout << "folder/db created at " << db_path_name << endl;
}
