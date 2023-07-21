#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
#include <vector>
#include <array>

class Snowflake : public Object3D {
public:
	bool is_stuck;
	bool is_stuck_on_chassi;
	Point3D position_on_chassi;
	Snowflake();
};