#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
#include <vector>

class Box: public Object3D {
public:
	Box();
	bool isPointInsideOfBox(const Point3D& point);
};