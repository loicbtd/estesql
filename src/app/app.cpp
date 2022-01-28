#include "app.h"

void app::start(int argc, char const *argv[]) {

    do {

        string sql;
        getline(cin, sql);

        if (sql == "exit") { break; }

        // if request not end with ';'
        while (sql.back() != ';') {
            cout << "--->";
            string temp;
            getline(cin, temp);
            sql.append(temp);
        }

        // put everything in lowercase
        for_each(sql.begin(), sql.end(), [](char & c) {
            c = ::tolower(c);
        });

        try {

            unique_ptr<sql_query> sql_query = query_generator::generate_query(sql);
            cout << "Query: " << sql_query->getQuery() << endl;
//        sql_query->check();
//        sql_query->expand();
//        sql_query->execute();

        } catch (custom_exception& e) {
            cout << e.what() << endl;
        }


        /*
        string first_word;
        first_word = sql.substr(0, sql.find(SPACE_DELIMITER));

        std::string delimiter = ">=";

        size_t pos = 0;
        std::string token;
        while ((pos = sql.find(delimiter)) != std::string::npos) {
            token = sql.substr(0, pos);
            std::cout << token << std::endl;
            sql.erase(0, pos + delimiter.length());
        }
        std::cout << sql << std::endl;*/


    } while (true);

}