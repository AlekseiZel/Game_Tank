#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include <vector>

class Object3D {
public:
	Point3D position;
	float elevator_angle;
	float dir_angle;
	float scale;
	float speed;
	uint32_t color;
	std::vector<Segment3D> figure;
	std::vector<Segment3D> absolut_figure;
	Object3D();
	void draw(uint32_t buffer[][SCREEN_WIDTH]);
};