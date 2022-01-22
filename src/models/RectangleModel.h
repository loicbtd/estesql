#ifndef RECTANGLE_MODEL

#include "interfaces/IShape.h"
#include <string>

#define RECTANGLE_MODEL

using namespace std;

class RectangleModel : public IShape {
protected:
    double width;
    double height;
public:
    RectangleModel();

    RectangleModel(const RectangleModel &rectangle);

    RectangleModel(RectangleModel &&rectangleModel) = default;

    RectangleModel(double, double);

    double CalculatePerimeter();

    double CalculateSurface();

    string GetName();
};

#endif
