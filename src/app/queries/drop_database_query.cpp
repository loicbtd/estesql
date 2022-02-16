#include "drop_database_query.h"

void drop_database_query::parse() {

    string str_regex ("drop (database|db) ");
    str_regex.append(get_db_name()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DROP_DB_SYNTAX);
    }

}

void drop_database_query::check() {

    parse();

    db_info* db_info = db_info::get_instance();
    string parent_db_folder_path = db_info->get_db_parent_folder_path();

    if (!db_table_utilities::exists(parent_db_folder_path.append("/").append(get_db_name()).c_str())) {
        throw non_existing_db_exception();
    }


}

void drop_database_query::expand() {}

void drop_database_query::execute() {

    db_info* db_info = db_info::get_instance();
    string parent_db_folder_path = db_info->get_db_parent_folder_path();

    if (get_db_name() == db_info->get_db_name()) {
        cout << "You dropped the current database. Please restart the program to access another database." << endl;
        db_table_utilities::delete_db_or_table_folder(db_info->get_current_db_path());
        exit(0);
    }

    db_table_utilities::delete_db_or_table_folder(parent_db_folder_path.append("/").append(get_db_name()));

}
