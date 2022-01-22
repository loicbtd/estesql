#include "app.h"
#include "app/queries/sql_query.h"

void app::start(int argc, char const *argv[]) {

    while(true) {

        string sql;
        cin >> sql;
        if (sql == "exit") { break; }

        /*try {
            unique_ptr<sql_query> query = query_factory::generate_query(sql) ;
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