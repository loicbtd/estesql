#ifndef CIRCLE_MODEL

#include "interfaces/IShape.h"
#include <string>

#define CIRCLE_MODEL

using namespace std;

class CircleModel : public IShape {
protected:
    double radius;
public:
    CircleModel(double);

    double CalculatePerimeter();

    double CalculateSurface();

    string GetName();
};

#endif
