#include "drop_table_query.h"
#include "app/managers/db_info.h"
#include "app/helpers/db_table_utilities.h"

void drop_table_query::parse() {

    string str_regex ("drop table ");
    str_regex.append(getTableName()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(DROP_TABLE_SYNTAX);
    }

}

void drop_table_query::check() {

    parse();

    db_info* db_info = db_info::get_instance();
    string db_folder_path = db_info->getCurrentDbPath();

    string table_path = db_folder_path.append("/").append(getTableName());

    if (!db_table_utilities::exists(table_path.c_str())) {
        throw non_existing_table_exception();
    }

}

void drop_table_query::expand() {}

void drop_table_query::execute() {

    db_info* db_info = db_info::get_instance();
    string db_folder_path = db_info->getCurrentDbPath();

    db_table_utilities::delete_db_or_table_folder(db_folder_path.append("/").append(getTableName()));

}
