#include <iterator>
#include <vector>
#include "query_singleton.h"

query_singleton* query_singleton::singleton_= nullptr;;


query_singleton *query_singleton::GetInstance() {
    if(singleton_==nullptr){
        singleton_ = new query_singleton();
    }
    return singleton_;
}

//TODO check first word => create proper query or throw exception => return unique_ptr of sql_query
unique_ptr<sql_query> query_singleton::query_generator(string sql) {

    string first_word = sql.substr(0, sql.find(SPACE_DELIMITER));

    bool is_query = false;

    for (int i = 0; i < NUMBER_OF_QUERIES; ++i) {

        if (first_word == enum_str[i]) {
            is_query = true;
            break;
        }

    }

    if (is_query) {

    } else {
        //todo throw exception
    }

    return unique_ptr<sql_query>();
}

bool query_singleton::test(const string& sql) {

    string first_word;
    first_word = sql.substr(0, sql.find(SPACE_DELIMITER));

    bool is_query = false;

    for (int i = 0; i < NUMBER_OF_QUERIES; ++i) {
        if (first_word == enum_str[i]) {
            is_query = true;
            break;
        }
    }

    if (is_query) {
        cout << first_word << " blup " << endl;
        return is_query;
    } else {
        throw ;
    }

}
