#ifndef SHAPE_FACTORY

#include "interfaces/IShape.h"
#include "models/CircleModel.h"
#include "models/RectangleModel.h"
#include "models/TriangleModel.h"

#define SHAPE_FACTORY

class ShapeFactory {
protected:
    ShapeFactory();

    static ShapeFactory *singleton_;

public:
    ShapeFactory(ShapeFactory &other) = delete;

    ~ShapeFactory();

    void operator=(const ShapeFactory &) = delete;

    static ShapeFactory *GetInstance();

    static CircleModel *ConstructCircle(double);

    static RectangleModel *ConstructRectangle(double, double);

    static TriangleModel *ConstructTriangle(double, double, double);
};

#endif
