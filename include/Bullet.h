#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
#include <vector>

class Bullet : public Object3D {
public:

	Point3D direction;
	Bullet();
};