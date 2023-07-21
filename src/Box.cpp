#include "Box.h"
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include <vector>

Box::Box() {

	scale = 50;
	color = 0xA0522D;// 0x8B4513;// 0x00FF0000;

	figure.push_back(Segment3D(Point3D(0.0f, 0.0f, 0.0f), Point3D(1.0f, 0.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 0.0f, 0.0f), Point3D(0.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 0.0f, 0.0f), Point3D(0.1f, 0.1f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.9f, 0.9f, 1.0f), Point3D(0.1f, 0.9f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.9f, 0.9f, 1.0f), Point3D(0.9f, 0.1f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.9f, 0.9f, 1.0f), Point3D(1.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.1f, 0.1f, 1.0f), Point3D(0.1f, 0.9f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.1f, 0.1f, 1.0f), Point3D(0.9f, 0.1f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 1.0f, 0.0f), Point3D(0.1f, 0.9f, 1.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 1.0f, 0.0f), Point3D(1.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(1.0f, 0.0f, 0.0f), Point3D(0.9f, 0.1f, 1.0f)));
	figure.push_back(Segment3D(Point3D(1.0f, 0.0f, 0.0f), Point3D(1.0f, 1.0f, 0.0f)));

	for (auto& segment : figure) {
		segment.point_a.x *= scale;
		segment.point_a.y *= scale;
		segment.point_a.z *= scale;

		segment.point_b.x *= scale;
		segment.point_b.y *= scale;
		segment.point_b.z *= scale;
	}
}
bool Box::isPointInsideOfBox(const Point3D& point) {

	if ((position.z < point.z + 5.0f) && ((position.z + scale) > point.z) &&
		(position.y < point.y) && ((position.y + scale) > point.y) &&
		(position.x < point.x) && ((position.x + scale) > point.x))
		return true;
	else
		return false;
}
