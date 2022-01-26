#include "query_generator.h"


unique_ptr<sql_query> query_generator::generate_query(const string& sql) {

    stringstream ss(sql);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vector_strings(begin, end);

    string first_word = vector_strings.front();

    for (int i = 0; i < NUMBER_OF_QUERIES; ++i) {

        if (first_word == enum_str[i]) {

            if ((vector_strings.size() < 3) && ((i == 0) || (i == 5))) {
                throw query_size_exception();
            }

            string second_word = next(vector_strings.begin())->data();

            switch (i) {

                case 0:

                    if (second_word == TABLE) {
                        return move(make_unique<create_table_query>(sql));
                    } else if ((second_word == DATABASE) || (second_word == DB)) {
                        return move(make_unique<create_database_query>(sql));
                    } else {
                        throw create_drop_table_or_db_exception();
                    }

                case 1:
                    return move(make_unique<select_query>(sql));
                case 2:
                    return move(make_unique<insert_query>(sql));
                case 3:
                    return move(make_unique<update_query>(sql));
                case 4:
                    return move(make_unique<delete_query>(sql));

                case 5:

                    if (second_word == TABLE) {
                        return move(make_unique<drop_table_query>(sql));
                    } else if ((second_word == DATABASE) || (second_word == DB)) {
                        return move(make_unique<drop_database_query>(sql));
                    } else {
                        throw create_drop_table_or_db_exception();
                    }

                case 6:
                    return move(make_unique<use_query>(sql));

            }

        }

    }

    throw unknown_query_exception();

}
