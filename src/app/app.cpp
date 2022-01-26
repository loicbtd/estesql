#include "app.h"
#include "app/queries/sql_query.h"

#include "app/enumerations/query_type.h"
#include "app/queries/query_generator.h"

#include <memory>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

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

//        query_generator* singleton = query_generator::GetInstance();
        unique_ptr<sql_query> sql_query = query_generator::generate_query(sql);
        cout << "Query: " << sql_query->getQuery() << endl;
//        sql_query->parse();
//        sql_query->check();
//        sql_query->expand();
//        sql_query->execute();

        /*std::string delimiter = ">=";

        size_t pos = 0;
        std::string token;
        while ((pos = sql.find(delimiter)) != std::string::npos) {
            token = sql.substr(0, pos);
            std::cout << token << std::endl;
            sql.erase(0, pos + delimiter.length());
        }
        std::cout << sql << std::endl;*/

        /*try {
            unique_ptr<sql_query> query = query_factory::generate_query(sql);
            query->check();
            query->expand();
            query->execute();
        } catch (unknown_sql_exception &e) {

        } catch (sql_exception &e) {

        } catch (check_exception &e) {

        } catch (expand_exception &e) {

        } catch (execute_exception &e) {

        } catch (exception & e) {
        }*/


    } while (true);

}