#ifndef ESTESQL_TEST_BASE_H
#define ESTESQL_TEST_BASE_H

#include <string>
#include <map>


using namespace std;

class test_base {
public:
    virtual string name() = 0;
    virtual map<string, bool> passTests() = 0;
};


#endif //ESTESQL_TEST_BASE_H
