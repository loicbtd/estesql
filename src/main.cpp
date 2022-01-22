#include <iostream>
#include "factories/ShapeFactory.h"
#include "services/ShapeService.h"

using namespace std;

int main() {

    ShapeFactory *shapeFactory = ShapeFactory::GetInstance();

    CircleModel *circle = shapeFactory->ConstructCircle(10);
    RectangleModel *rectangle = shapeFactory->ConstructRectangle(10, 10);
    TriangleModel *triangle = shapeFactory->ConstructTriangle(10, 10, 10);

    ShapeService *shapeService = new ShapeService();

    shapeService->Add(circle);
    shapeService->Add(triangle);
    shapeService->Add(rectangle);

    for (IShape *&shape: shapeService->RetrieveAll()) {
        cout << shape->GetName() << " " << "perimeter: " << shape->CalculatePerimeter() << endl;
        cout << shape->GetName() << " " << "surface: " << shape->CalculateSurface() << endl;
    }

    cout << endl << endl;

    RectangleModel *rectangleConstructedByDefault = new RectangleModel();
    RectangleModel *rectangleConstructedByCopy = new RectangleModel(*rectangleConstructedByDefault);
    RectangleModel *rectangleConstructedByMove = move(rectangleConstructedByDefault);

    cout << "Rectangle constructed by default address: " << &rectangleConstructedByDefault << endl;
    cout << "Rectangle constructed by copy address: " << &rectangleConstructedByCopy << endl;
    cout << "Rectangle constructed by move address: " << &rectangleConstructedByMove << endl;

    cout << endl << endl;

    shapeService->Initialize(vector<IShape *>());
    shapeService->GenerateRandomData();
    shapeService->Add(new TriangleModel(10, 10, 10));

    for (IShape *&shape: shapeService->RetrieveAll()) {
        cout << shape->CalculateSurface() << endl;
    }

    return 0;
}
