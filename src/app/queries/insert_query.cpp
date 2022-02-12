#include "insert_query.h"

void insert_query::parse() {

    string str_regex ("insert into ");
    str_regex.append(getTableName()).append(" \\\([a-z0-9_-]+(( )?,( )?[a-z0-9_-]+)*\\\) values \\\(('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*\\\)( )?;");
    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(INSERT_SYNTAX);
    }

}

void insert_query::check() {

    parse();

    //Todo 1 retrieve all columns from query -> vector<string>
    //Todo 2 retrieve all values -> vector<string>
    //Todo 3 check if nb columns == nb values -> size1 == size2
    //Todo 4 retrieve all columns from definition_file get_table_definition().getColumns()
    //Todo 5 compare types values/columns from definition_file -> check if "'"
    //Todo 6 primary_key management


}

void insert_query::expand() {}

void insert_query::execute() {

}
