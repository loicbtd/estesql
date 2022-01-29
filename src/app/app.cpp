#include "app.h"

void app::start(int argc, char const *argv[]) {

    db_info* db_current = db_info::GetInstance();

    if(!usage(argc, argv, db_current)) {
        cout << "Usage blopblopblopblop" << endl;
        exit(-1);
    }

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

bool app::usage(int argc, const char **argv, db_info* db_info) {

    if (argc != 5) {
        return false;
    }

    string db_name; // -d param

    if (argv[1]=="-d") {
        db_name = argv[2];
    } else if (argv[3]=="-d") {
        db_name = argv[4];
    } else {
        cout << "parameters -d not found" << endl;
        return false;
    }

    string db_parent_folder_path; // -l param

    if (argv[1]=="-l") {
        db_parent_folder_path = argv[2];
    } else if (argv[3]=="-l") {
        db_parent_folder_path = argv[4];
    } else {
        cout << "parameters -l not found" << endl;
        return false;
    }


    if (db_utilities::exists(db_parent_folder_path)) {

        string db_path = db_parent_folder_path.append("/").append(db_name);

        if (!db_utilities::exists(db_name)) {
            create_database_query new_db = create_database_query();
            new_db.createDb(db_name);
        }

        db_info->setCurrentDbPath(db_path);
        return true;

    }

    return false;
}
