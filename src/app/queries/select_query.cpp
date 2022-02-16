#include "select_query.h"


void select_query::parse() {

    string all_columns("select * from ");

    if (get_query().find(all_columns) != string::npos) {
        expand();
    }

    string str_regex ("select [a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)* from ");
    str_regex.append(get_table_name());

    string where_clause = " where ";
    smatch smatch_;

    if (regex_search(get_query(), smatch_, regex(where_clause))) {
        str_regex.append(" where [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+)*( )?;");
    } else {
        str_regex.append("( )?;");
    }

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(SELECT_SYNTAX);
    }

}

void select_query::check() {

    parse();

    /*string current_db_path = db_info::get_instance()->get_current_db_path();
    if (db_table_utilities::exists(current_db_path.append("/").append(get_table_name()).c_str())) {
        throw non_existing_table_exception();
    }*/

    //Todo 1 retrieve all columns from query
    smatch smatch_;
    string columns = "select [a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)* from ";
    string columns_str;

    if (regex_search(get_query(), smatch_, regex(columns))) {
        columns_str = smatch_.str();
    }
    columns_str = string_utilities::erase_substring(columns_str, "select ");
    columns_str = string_utilities::erase_substring(columns_str, " from ");

    vector<string> columns_select_vector = string_utilities::convert_string_to_vector_delimiter(columns_str, COMA_DELIMITER);

    for (auto str: columns_select_vector) {
        cout << str << endl;
    }

    //Todo 2 retrieve all columns from definition_file
    //Todo 3 check if all columns from query exists
    //Todo 4 put all columns in the right order
    //Todo 5 set

}

void select_query::expand() {
//TODO retrieve all columns from the tableName and replace '*' by them seprated by ','

    cout << "expand()" << endl;

}

void select_query::execute() {

    //Todo 1 retrieve infos set in check()
    //Todo 2 read content_file
    //Todo 3 print table

}
