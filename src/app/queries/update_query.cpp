#include "update_query.h"

void update_query::parse() {

    string str_regex ("update ");
    str_regex.append(get_table_name()).append(" set [a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?)(( )?,( )?[a-z0-9_-]+( )?=( )?('[a-z0-9_-]+'|[0-9]+(.[0-9]+)?))*");

    string where_clause = " where ";
    smatch smatch_;

    if (regex_search(get_query(), smatch_, regex(where_clause))) {

        str_regex.append(" where [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+( (and|or) [a-z0-9_-]+( )?(<=|>=|=|<>|>|<)( )?[a-z0-9_-]+)*( )?;");
        set_is_where_clause(true);

    } else {

        str_regex.append("( )?;");
        set_is_where_clause(false);

    }

    regex regex_ (str_regex);

    if (!regex_match(get_query(), regex_)) {
        throw slq_invalid_syntax_exception(UPDATE_SYNTAX);
    }

}

void update_query::check() {

    parse();

    string current_db_path = db_info::get_instance()->get_current_db_path();
    if (db_table_utilities::exists(current_db_path.append("/").append(get_table_name()).c_str())) {
        throw non_existing_table_exception();
    }

    //Todo 2.2 retrieve all columns from definition_file
    vector<string> columns_name_from_file = definition_file::get_instance()->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file::get_instance()->get_all_columns_types();




    if (is_where_clause_get()) {
        set_where_clause(build_where_clause::build_where(get_query(), UPDATE_SYNTAX, columns_name_from_file));
    }

}

void update_query::expand() {

}

void update_query::execute() {

}


bool update_query::is_where_clause_get() const {
    return is_where_clause;
}

void update_query::set_is_where_clause(bool isWhereClause) {
    is_where_clause = isWhereClause;
}

const where_clause &update_query::get_where_clause() const {
    return where_clause;
}

void update_query::set_where_clause(const class where_clause &whereClause) {
    where_clause = whereClause;
}
