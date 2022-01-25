#include "app.h"
#include "app/queries/sql_query.h"

#include "app/enumerations/query_type.h"

#include <memory>

void app::start(int argc, char const *argv[]) {

    while(true) {

        string sql;
        cin >> sql;

        if (sql == "exit") { break; }

        // if request not end with ';'
        while (sql.back() != ';') {
            cout << "--->";
            string temp;
            cin >> temp;
            sql.append(temp);
        }

//        unique_ptr<sql_query> query = query_factory::generate_query(sql);
//        query->check();
//        query->expand();
//        query->execute();

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

    }

}