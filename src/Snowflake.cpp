#include "Snowflake.h"
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include <vector>

Snowflake::Snowflake() {

	speed = 1.0f;
	scale = 5;
	color = 0x4682B4;// 0x6A5ACD;

	is_stuck = false;
	is_stuck_on_chassi = false;

	figure.push_back(Segment3D(Point3D(0.0f, -2.0f, 0.0f), Point3D(0.0f, 2.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 0.0f, -2.0f), Point3D(0.0f, 0.0f, 2.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, -1.5f, -0.5f), Point3D(0.0f, -1.5f, 0.5f)));
	figure.push_back(Segment3D(Point3D(0.0f, 1.5f, -0.5f), Point3D(0.0f, 1.5f, 0.5f)));
	figure.push_back(Segment3D(Point3D(0.0f, -0.5f, -1.5f), Point3D(0.0f, 0.5f, -1.5f)));
	figure.push_back(Segment3D(Point3D(0.0f, -0.5f, 1.5f), Point3D(0.0f, 0.5f, 1.5f)));

	for (auto& segment : figure){

		segment.point_a.x *= scale;
		segment.point_a.y *= scale;
		segment.point_a.z *= scale;

		segment.point_b.x *= scale;
		segment.point_b.y *= scale;
		segment.point_b.z *= scale;
	}
}
