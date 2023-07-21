#include "Point3D.h"
#include <array>



Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

Point3D Point3D::applyTransformation(const std::array<std::array<float, 4>, 4>& translationMatrix) {
    Point3D newPoint({ 0.f,0.f,0.f });

    float currPoint[4] = { x, y, z, 1.0f };
    float translatedPoint[3] = { 0.0f };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            translatedPoint[i] += translationMatrix[i][j] * currPoint[j];
        }
    }
    newPoint.x = translatedPoint[0];
    newPoint.y = translatedPoint[1];
    newPoint.z = translatedPoint[2];

    return newPoint;
}
