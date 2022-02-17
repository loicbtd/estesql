#include "where_clause.h"

const vector<pair<string, vector<string>>> &where_clause::get_elements() const {
    return elements;
}

void where_clause::set_elements(const vector<pair<string, vector<string>>> &elements) {
    where_clause::elements = elements;
}

const string &where_clause::get_type() const {
    return type;
}

void where_clause::set_type(const string &type) {
    where_clause::type = type;
}

bool where_clause::is_where_clause_apply(vector<vector<uint8_t>> record, const vector<string>& columns_names, const vector<field_type_t>& columns_types) {

    if (type == "or") {
        // stop to first true and return true

        for (int i = 0; i < columns_names.size(); ++i) {

            for (int j = 0; j < elements.size(); ++j) {
                if (elements.at(j).second.at(0) == columns_names.at(i)) {

                    vector<uint8_t> values_where_clause;

                    switch (columns_types.at(i)) {
                        case INT:
                            values_where_clause = db_table_utilities::int_to_binary_string_to_vector(stoll(elements.at(j).second.at(1)));
                            break;
                        case FLOAT:
                            values_where_clause = db_table_utilities::float_to_binary_string_to_vector(stod(elements.at(j).second.at(1)));
                            break;
                        case PRIMARY_KEY:
                            values_where_clause = db_table_utilities::primary_key_to_binary_string_to_vector(stoull(elements.at(j).second.at(1)));
                            break;
                        case TEXT:
                            string value = string_utilities::format_string_for_uint8_t( elements.at(j).second.at(1));
                            vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
                            values_where_clause = string_utilities::append_vector_uint8t_into_another(values_where_clause, str_to_uint8_t_vector);
                            break;

                    }

                    if (db_table_utilities::compare_vector_uint8_t(record.at(i), values_where_clause)) {
                        return true;
                    }

                    break;
                }
            }


        }

        return false;


    } else {
        // stop to first false and return false

        for (int i = 0; i < columns_names.size(); ++i) {

            for (int j = 0; j < elements.size(); ++j) {
                if (elements.at(j).second.at(0) == columns_names.at(i)) {

                    vector<uint8_t> values_where_clause;

                    switch (columns_types.at(i)) {
                        case INT:
                            values_where_clause = db_table_utilities::int_to_binary_string_to_vector(stoll(elements.at(j).second.at(1)));
                            break;
                        case FLOAT:
                            values_where_clause = db_table_utilities::float_to_binary_string_to_vector(stod(elements.at(j).second.at(1)));
                            break;
                        case PRIMARY_KEY:
                            values_where_clause = db_table_utilities::primary_key_to_binary_string_to_vector(stoull(elements.at(j).second.at(1)));
                            break;
                        case TEXT:
                            string value = string_utilities::format_string_for_uint8_t( elements.at(j).second.at(1));
                            vector<uint8_t> str_to_uint8_t_vector(value.begin(), value.end());
                            values_where_clause = string_utilities::append_vector_uint8t_into_another(values_where_clause, str_to_uint8_t_vector);
                            break;

                    }

                    if (!db_table_utilities::compare_vector_uint8_t(record.at(i), values_where_clause)) {
                        return false;
                    }

                    break;
                }
            }


        }

        return true;

    }

}
