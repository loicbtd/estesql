#include "CircleModel.h"
#include <cmath>

CircleModel::CircleModel(double radius) {
    this->radius = radius;
}

double CircleModel::CalculatePerimeter() {
    return 2 * M_PI * radius;
}

double CircleModel::CalculateSurface() {
    return M_PI * radius * radius;
}

string CircleModel::GetName() {
    return "Circle";
}