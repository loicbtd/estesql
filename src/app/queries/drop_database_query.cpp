#include "drop_database_query.h"

void drop_database_query::parse() {

    string str_regex ("drop (database|db) ");
    str_regex.append(getDbName()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DROP_DB_SYNTAX);
    }

}

void drop_database_query::check() {

    parse();

    db_info* db_info = db_info::GetInstance();
    string parent_db_folder_path = db_info->getDbParentFolderPath();

    if (!db_table_utilities::exists(parent_db_folder_path.append("/").append(getDbName()).c_str())) {
        throw non_existing_db_exception();
    }


}

void drop_database_query::expand() {}

void drop_database_query::execute() {

    db_info* db_info = db_info::GetInstance();
    string parent_db_folder_path = db_info->getDbParentFolderPath();

    if (getDbName() == db_info->getDbName()) {
        cout << "You dropped the current database. Please restart the program to access another database." << endl;
        db_table_utilities::delete_db_or_table_folder(db_info->getCurrentDbPath());
        exit(0);
    }

    db_table_utilities::delete_db_or_table_folder(parent_db_folder_path.append("/").append(getDbName()));

}
