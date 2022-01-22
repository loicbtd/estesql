#include "ShapeFactory.h"


ShapeFactory *ShapeFactory::singleton_ = nullptr;

ShapeFactory::ShapeFactory() {}

ShapeFactory *ShapeFactory::GetInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new ShapeFactory();
    }
    return singleton_;
}

CircleModel *ShapeFactory::ConstructCircle(double radius) {
    return new CircleModel(radius);
}

RectangleModel *ShapeFactory::ConstructRectangle(double width, double heigth) {
    return new RectangleModel(width, heigth);
}

TriangleModel *ShapeFactory::ConstructTriangle(double sideALength, double sideBLength, double sideCLength) {
    return new TriangleModel(sideALength, sideBLength, sideCLength);
}

ShapeFactory::~ShapeFactory() {}
