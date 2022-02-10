#include "create_database_query.h"

void create_database_query::parse() {

    string str_regex ("create (database|db) ");
    str_regex.append(getDbName()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(CREATE_DB_SYNTAX);
    }

}

void create_database_query::check() {

    parse();

}

void create_database_query::expand() {

}

void create_database_query::execute() {

}

create_database_query::create_database_query() {

}

void create_database_query::createDb(string db_path_name) {
    fs::create_directory(db_path_name);
    cout << "folder/db created at " << db_path_name << endl;
}
