#include <random>
#include <functional>
#include "interfaces/IShape.h"

#include "ShapeService.h"
#include "factories/ShapeFactory.h"

using namespace std;

ShapeService::ShapeService() {}

void ShapeService::Add(IShape *shape) {
    this->shapes.push_back(shape);

    sort(this->shapes.begin(), this->shapes.end(), [](IShape *shape1, IShape *shape2) {

        return shape1->CalculateSurface() < shape2->CalculateSurface();
    });
}

vector<IShape *> ShapeService::RetrieveAll() {
    return this->shapes;
}

void ShapeService::GenerateRandomData() {
    static auto randomBoolean = bind(uniform_int_distribution<>(0, 1), default_random_engine());
    uniform_real_distribution<double> randomDoubleGenerator(0, 100);
    default_random_engine randomEngine;

    for (int index = 0; index < 10; ++index) {
        if (randomBoolean()) {
            this->shapes.push_back(
                    new RectangleModel(
                            randomDoubleGenerator(randomEngine),
                            randomDoubleGenerator(randomEngine)
                    )
            );
        } else {
            this->shapes.push_back(
                    new TriangleModel(
                            randomDoubleGenerator(randomEngine),
                            randomDoubleGenerator(randomEngine),
                            randomDoubleGenerator(randomEngine)
                    )
            );
        }
    }
}

void ShapeService::Initialize(vector<IShape *> list) {
    this->shapes = list;
}

void ShapeService::Delete(int position) {
    this->shapes.erase(next(this->shapes.begin(), position));
}

ShapeService::~ShapeService() {
    this->shapes.empty();
}


