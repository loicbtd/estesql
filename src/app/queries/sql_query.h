#ifndef SQL_QUERY
#define SQL_QUERY

#include <iostream>

using namespace std;

class sql_query {

private:
    string query;

public:

    sql_query() {}
    sql_query(string sql): query(sql) {}

    const string &get_query() const;

    void set_query(const string &query);

    virtual void parse()=0;
    virtual  void check()=0;
    virtual void expand()=0;
    virtual void execute()=0;
};

#endif