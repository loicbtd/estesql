#ifndef SHAPE_INTERFACE

#include <string>

#define SHAPE_INTERFACE

using namespace std;

class IShape {
public:
    virtual ~IShape();

    virtual double CalculatePerimeter();

    virtual double CalculateSurface();

    virtual string GetName();
};

#endif
