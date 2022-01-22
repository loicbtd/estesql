#include "RectangleModel.h"

RectangleModel::RectangleModel() {
    this->width = 20;
    this->height = 10;
}

RectangleModel::RectangleModel(const RectangleModel &rectangle) {
    this->width = rectangle.width;
    this->height = rectangle.height;
}

RectangleModel::RectangleModel(double width, double height) {
    this->width = width;
    this->height = height;
}

double RectangleModel::CalculatePerimeter() {
    return 2 * width + 2 * height;
}

double RectangleModel::CalculateSurface() {
    return width * height;
}

string RectangleModel::GetName() {
    return "Rectangle";
}

