#include "select_query.h"

void select_query::parse() {

    smatch smatch_;
    string all_columns_regex("select \* from ");
    all_columns_regex.append(getTableName()).append("( )?;");
    cout << all_columns_regex <<endl;

    if (regex_search(getQuery(), smatch_, regex(all_columns_regex))) {
        cout << "blop" << endl;
        expand();
    }

    string str_regex ("select [a-z_-]+(( )?,( )?[a-z_-]+)* from ");
    str_regex.append(getTableName()).append("( where [a-z_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z_-]+( (AND|OR) [a-z_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z_-]+)*|)( )?;");

    regex regex_ (str_regex);

    if (!regex_match(getQuery(), regex_)) {
        throw slq_invalid_syntax_exception(SELECT_SYNTAX);
    }

}

void select_query::check() {

    parse();

}

void select_query::expand() {
//TODO retrieve all columns from the tableName and replace '*' by them seprated by ','
}

void select_query::execute() {

}
