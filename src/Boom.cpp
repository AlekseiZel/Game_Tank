#include "Boom.h"
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
//#include <vector>

Boom::Boom() {

	scale = 2;
	speed = 70;
	color = 0xFFD700;

	figure.push_back(Segment3D(Point3D(-3.0f, 0.0f, 0.0f), Point3D(-2.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(-3.0f, 3.0f, 0.0f), Point3D(-2.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(-3.0f, 3.0f, 0.0f), Point3D(-1.0f, 2.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 3.0f, 0.0f), Point3D(-1.0f, 2.0f, 0.0f)));

	figure.push_back(Segment3D(Point3D(3.0f, 0.0f, 0.0f), Point3D(2.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(3.0f, 3.0f, 0.0f), Point3D(2.0f, 1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(3.0f, 3.0f, 0.0f), Point3D(1.0f, 2.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, 3.0f, 0.0f), Point3D(1.0f, 2.0f, 0.0f)));

	figure.push_back(Segment3D(Point3D(3.0f, 0.0f, 0.0f), Point3D(2.0f, -1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(3.0f, -3.0f, 0.0f), Point3D(2.0f, -1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(3.0f, -3.0f, 0.0f), Point3D(1.0f, -2.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, -3.0f, 0.0f), Point3D(1.0f, -2.0f, 0.0f)));

	figure.push_back(Segment3D(Point3D(-3.0f, 0.0f, 0.0f), Point3D(-2.0f, -1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(-3.0f, -3.0f, 0.0f), Point3D(-2.0f, -1.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(-3.0f, -3.0f, 0.0f), Point3D(-1.0f, -2.0f, 0.0f)));
	figure.push_back(Segment3D(Point3D(0.0f, -3.0f, 0.0f), Point3D(-1.0f, -2.0f, 0.0f)));

}
bool Boom::isPointInsideBoom(const Point3D& point) {

	if ((position.z < point.z + 5.0f) && ((position.z + scale) > point.z) &&
		(position.y < point.y) && ((position.y + scale) > point.y) &&
		(position.x < point.x) && ((position.x + scale) > point.x))
		return true;
	else
		return false;
}

