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

    for (int i = 0; i < columns_names.size(); ++i) {

        for (int j = 0; j < elements.size(); ++j) {

            if (elements.at(j).second.at(0) == columns_names.at(i)) {

                bool compare_result;
                long long record_value_ll;
                unsigned long long record_value_ull;
                double record_value_d;
                string record_value_str;

                switch (columns_types.at(i)) {

                    case INT:

                        record_value_ll = db_table_utilities::uint8_t_vector_to_long_long(record.at(i));
                        compare_result = db_table_utilities::compare_INT(record_value_ll, stoll(elements.at(j).second.at(1)), elements.at(j).first);
                        break;

                    case FLOAT:

                        record_value_d = db_table_utilities::uint8_t_vector_to_double(record.at(i));
                        compare_result = db_table_utilities::db_table_utilities::compare_FLOAT(record_value_d, stod(elements.at(j).second.at(1)), elements.at(j).first);
                        break;

                    case PRIMARY_KEY:

                        record_value_ull = db_table_utilities::uint8_t_vector_to_unsigned_long_long(record.at(i));
                        compare_result = db_table_utilities::compare_P_K(record_value_ull, stoull(elements.at(j).second.at(1)), elements.at(j).first);
                        break;

                    case TEXT:

                        record_value_str = db_table_utilities::uint8_t_vector_to_string(record.at(i));
                        compare_result = db_table_utilities::compare_STR(record_value_str, elements.at(j).second.at(1), elements.at(j).first);
                        break;

                }

                if ((type == "or") && compare_result) {                   // stop to first true and return true
                    return true;
                } else if ((type == "and") && !compare_result) {          // stop to first false and return false
                    return false;
                }

                break;
            }

        }

    }

    if (type == "or") {                                                  // all false
        return false;
    } else if (type == "and") {                                          // all true
        return true;
    }

}


