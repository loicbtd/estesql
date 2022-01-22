#ifndef SHAPE_SERVICE

#include <vector>
#include <random>
#include <functional>
#include <iostream>
#include "interfaces/IShape.h"

#define SHAPE_SERVICE

using namespace std;

class ShapeService {
private:
    vector<IShape *> shapes;

public:
    ShapeService();

    void Add(IShape *);

    vector<IShape *> RetrieveAll();

    void Initialize(vector<IShape *>);

    void Delete(int);

    void GenerateRandomData();

    virtual ~ShapeService();


};

#endif
