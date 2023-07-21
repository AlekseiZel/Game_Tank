#pragma once
#include <array>


class Point3D {
public:
	float x, y, z;
	Point3D();
	Point3D(float x, float y, float z);
	Point3D applyTransformation(const std::array<std::array<float, 4>, 4>& rotationMatrix);
};