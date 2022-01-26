#include <iterator>
#include <vector>

#include "app/constants/string_key_words.h"

#include "query_generator.h"
#include "create_table_query.h"
#include "create_database_query.h"
#include "drop_table_query.h"
#include "drop_database_query.h"
#include "select_query.h"
#include "insert_query.h"
#include "update_query.h"
#include "delete_query.h"
#include "use_query.h"


unique_ptr<sql_query> query_generator::generate_query(const string& sql) {

//    string first_word;
//    first_word = sql.substr(0, sql.find(SPACE_DELIMITER));

    stringstream ss(sql);
    istream_iterator<std::string> begin(ss);
    istream_iterator<std::string> end;
    vector<std::string> vstrings(begin, end);

    string first_word = vstrings.front();

    for (int i = 0; i < NUMBER_OF_QUERIES; ++i) {

        if (first_word == enum_str[i]) {

            if ((vstrings.size() < 2) && ((i==0)||(i==5))) {
                cout << "throw size < 2" << endl;
                throw ;
            }

            string second_word = next(vstrings.begin())->data();

            switch (i) {

                case 0:

                    if (second_word == TABLE) {
                        cout << "create table" << endl;
                        return move(make_unique<create_table_query>(sql));
                    } else if ((second_word == DATABASE) || (second_word == DB)) {
                        cout << "create database" << endl;
                        return move(make_unique<create_database_query>(sql));
                    } else {
                        cout << "throw second not correct CREATE" << endl;
                        throw ;
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
                        cout << "drop table" << endl;
                        return move(make_unique<drop_table_query>(sql));
                    } else if ((second_word == DATABASE) || (second_word == DB)) {
                        cout << "drop database" << endl;
                        return move(make_unique<drop_database_query>(sql));
                    } else {
                        cout << "throw second not correct DROP" << endl;
                        throw ;
                    }

                case 6:
                    return move(make_unique<use_query>(sql));

            }

        }

    }

    cout << "throw non valid query (first word)" << endl;
    throw ;

}
