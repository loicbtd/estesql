#include "delete_query.h"

void delete_query::parse() {

    string str_regex ("delete from ");
    str_regex.append(get_table_name());

    string where_clause_rgx = " where ";
    smatch smatch_;

    if (regex_search(get_query(), smatch_, regex(where_clause_rgx))) {

        str_regex.append(" where [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(>|<|<=|>=|=|<>)( )?[a-z0-9_-]+)*( )?;");
        set_is_where_clause(true);

    } else {

        str_regex.append("( )?;");
        set_is_where_clause(false);

    }

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(DELETE_SYNTAX);
    }

}

void delete_query::check() {

    parse();

    definition_file* definition_file = definition_file::get_instance();

    if (!definition_file->exists()) {
        throw non_existing_table_exception();
    }


    if (is_where_clause_get()) {
        vector<string> columns_name_from_file = definition_file->get_all_columns_names();
        set_where_clause(build_where_clause::build_where(get_query(), DELETE_SYNTAX, columns_name_from_file));
    }


}

void delete_query::expand() {}

void delete_query::execute() {




}


bool delete_query::is_where_clause_get() const {
    return is_where_clause;
}

void delete_query::set_is_where_clause(bool isWhereClause) {
    is_where_clause = isWhereClause;
}

const where_clause &delete_query::get_where_clause() const {
    return where_clause;
}

void delete_query::set_where_clause(const class where_clause &whereClause) {
    where_clause = whereClause;
}