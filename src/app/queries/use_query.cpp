#include "use_query.h"

void use_query::parse() {

    string str_regex ("use ");
    str_regex.append(get_db_name()).append("( )?;");

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(USE_SYNTAX);
    }

}

void use_query::check() {

    parse();

    db_info* db_info = db_info::get_instance();
    string db_path = db_info->get_db_parent_folder_path();
    db_path = db_path.append("/").append(get_db_name());

    if (!db_table_utilities::exists(db_path.c_str())) {
        throw non_existing_db_exception();
    }

}

void use_query::expand() {}

void use_query::execute() {

    file_set_up::set_up_source_file("");

    db_info* db_info = db_info::get_instance();
    string db_path = db_info->get_db_parent_folder_path();
    db_path = db_path.append("/").append(get_db_name());

    db_info->set_current_db_path(db_path);
    db_info->set_db_name(get_db_name());



}
