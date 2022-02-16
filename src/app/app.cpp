#include "app.h"

void app::start(int argc, char const *argv[]) {
    if (argc == 2 && strcmp(argv[1], "test") == 0) {
        cout << "Testing estesql..." << endl;

        vector<test_base *> tests = {
//                new content_file_should(),
//                new db_utilities_should(),
//                new definition_file_should(),
                new index_file_should(),
//                new key_file_should(),
//                new table_file_should(),
        };

        int successes_count = 0;
        int failures_count = 0;

        for (test_base *&test: tests) {
            for (auto const&[testName, result]: test->pass_tests()) {
                if (result) {
                    successes_count++;
                    cout << "[PASSED] " << test->name() << " " << testName << endl;
                } else {
                    failures_count++;
                    cout << "[FAILED] " << test->name() << " " << testName << endl;
                }
            }
        }

        cout << "SUCCESSES: " << successes_count << " / FAILURES: " << failures_count << endl;
        exit(0);
    }


    db_info *db_current = db_info::get_instance();

    if (!usage(argc, argv, db_current)) {
        cout << "Usage:" << endl;
        cout << "Inline parameters needed:" << endl;
        cout << "-l path/to/parent/folder/of/dataBase" << endl;
        cout << "-d name of the database folder" << endl;
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
        for_each(sql.begin(), sql.end(), [](char &c) {
            c = ::tolower(c);
        });

        try {

            unique_ptr<sql_query> sql_query = query_generator::generate_query(sql);
            cout << "Query: " << sql_query->get_query() << endl;
            // Todo retrieve singleton definition_file, then set source_file = get_table_name()
            sql_query->check();
            sql_query->execute();

        } catch (custom_exception &e) {
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

bool app::usage(int argc, const char **argv, db_info *db_info) {

    if (argc != 5) {
        return false;
    }

    string db_name; // -d param

    if (strcmp(argv[1], D_PARAM) == 0) {
        db_name = argv[2];
    } else if (strcmp(argv[3], D_PARAM) == 0) {
        db_name = argv[4];
    } else {
        cout << "parameter -d not found" << endl;
        return false;
    }

    string db_parent_folder_path; // -l param

    if (strcmp(argv[1], L_PARAM) == 0) {
        db_parent_folder_path = argv[2];
    } else if (strcmp(argv[3], L_PARAM) == 0) {
        db_parent_folder_path = argv[4];
    } else {
        cout << "parameter -l not found" << endl;
        return false;
    }

    if (db_table_utilities::exists(db_parent_folder_path.c_str())) {

        db_info->set_db_parent_folder_path(db_parent_folder_path);

        for_each(db_name.begin(), db_name.end(), [](char &c) {
            c = ::tolower(c);
        });

        string db_path = db_parent_folder_path.append("/").append(db_name);

        if (!db_table_utilities::exists(db_path.c_str())) {
            create_database_query new_db = create_database_query();
            new_db.create_db_at_path(db_path);
        }

        db_info->set_current_db_path(db_path);

        db_info->set_db_name(db_name);
        return true;

    }

    return false;
}