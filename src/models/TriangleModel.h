#ifndef TRIANGLE_MODEL

#include "interfaces/IShape.h"
#include <string>

#define TRIANGLE_MODEL

using namespace std;

class TriangleModel : public IShape {
protected:
    double sideALength;
    double sideBLength;
    double sideCLength;
public:
    TriangleModel(double, double, double);

    double CalculatePerimeter();

    double CalculateSurface();

    string GetName();
};

#endif
