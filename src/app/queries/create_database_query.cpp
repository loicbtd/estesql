#include "create_database_query.h"

void create_database_query::parse() {

}

void create_database_query::check() {

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
