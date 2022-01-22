#include "TriangleModel.h"
#include <cmath>

TriangleModel::TriangleModel(double sideALength, double sideBLength, double sideCLength) {
    this->sideALength = sideALength;
    this->sideBLength = sideBLength;
    this->sideCLength = sideCLength;
}

double TriangleModel::CalculatePerimeter() {
    return sideALength + sideBLength + sideCLength;
}

double TriangleModel::CalculateSurface() {
    double s = (sideALength + sideBLength + sideCLength) / 2;
    if (s > 0) {
        return sqrt(s * abs(s - sideALength) * abs(s - sideBLength) * abs(s - sideCLength));
    }
}

string TriangleModel::GetName() {
    return "Triangle";
}