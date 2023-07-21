#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
#include <vector>

class Boom : public Object3D {
public:

	Boom();
	bool isPointInsideBoom(const Point3D& point);
};
