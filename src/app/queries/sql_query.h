#ifndef SQL_QUERY

#include <iostream>

#define SQL_QUERY

using namespace std;

class sql_query {

private:
    string query;

public:

    sql_query() {}
    sql_query(string sql): query(sql) {}

    const string &getQuery() const;

    void setQuery(const string &query);

    virtual void parse()=0;
    virtual  void check()=0;
    virtual void expand()=0;
    virtual void execute()=0;
};

#endif