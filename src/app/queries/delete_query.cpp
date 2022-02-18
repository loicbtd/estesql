#include "delete_query.h"

void delete_query::parse() {

    definition_file* definition_file = definition_file::get_instance();

    if (!definition_file->exists()) {
        throw non_existing_table_exception();
    }

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

    if (is_where_clause_get()) {
        vector<string> columns_name_from_file = definition_file->get_all_columns_names();
        set_where_clause(build_where_clause::build_where(get_query(), DELETE_SYNTAX, columns_name_from_file));
    }


}

void delete_query::expand() {}

void delete_query::execute() {

    content_file* content_file = content_file::get_instance();
    vector<vector<uint8_t>> vector_all_records = content_file->retrieve_all();

    index_file* index_file = index_file::get_instance();
    vector<index_entry> vector_all_indexes = index_file->retrieve_all();

    definition_file* definition_file = definition_file::get_instance();
    vector<string> columns_name_from_file = definition_file->get_all_columns_names();
    vector<field_type_t> columns_type_from_file = definition_file->get_all_columns_types();

    if (!is_where_clause_get()) {

        for (auto & vector_all_indexe : vector_all_indexes) {

            if (vector_all_indexe.is_active) {

                index_entry index_entry;
                index_entry.is_active = false;
                index_entry.position = vector_all_indexe.position;
                index_entry.length = vector_all_indexe.length;
                index_file->write_index_entry(index_entry, index_entry.position);

            }

        }

    } else {

        for (int i = 0; i < vector_all_indexes.size(); ++i) {

            if (vector_all_indexes.at(i).is_active) {

                vector<uint8_t> record = vector_all_records.at(i);
                vector<vector<uint8_t>> columns_record = string_utilities::split_vector_with_type_length(record, columns_type_from_file);

                if (where_clause.is_where_clause_apply(columns_record, columns_name_from_file, columns_type_from_file)) {
                    index_entry index_entry;
                    index_entry.is_active = false;
                    index_entry.position = vector_all_indexes.at(i).position;
                    index_entry.length = vector_all_indexes.at(i).length;
                    index_file->write_index_entry(index_entry, index_entry.position);
                }

            }

        }

    }


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