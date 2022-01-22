#ifndef SQL_QUERY

#include <iostream>

#define SQL_QUERY

using namespace std;

class sql_query {
public:
    virtual void parse(string)=0;
    virtual  void check()=0;
    virtual void expand()=0;
    virtual void execute()=0;
};

#endif