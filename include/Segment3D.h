#pragma once
#include "Engine.h"
#include "Point3D.h"


class Segment3D {
public:
	Point3D point_a;
	Point3D point_b;
	uint32_t color;
	Segment3D();
	Segment3D(const Point3D& a, const Point3D& b);
	void draw(uint32_t buffer[][SCREEN_WIDTH]);
};