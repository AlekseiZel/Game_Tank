#include "Bullet.h"
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include <vector>

Bullet::Bullet() : direction(Point3D()){

	scale = 10;
    speed = 300.0f;
    direction.x = -1;
    color = 0xFF8C00;

    // снаряд
    figure.push_back(Segment3D(Point3D(0.0f, 0.12f, 0.25f), Point3D(0.0f, -0.12f, 0.25f)));
    figure.push_back(Segment3D(Point3D(0.0f, 0.12f, -0.25f), Point3D(0.0f, -0.12f, -0.25f)));
    figure.push_back(Segment3D(Point3D(0.0f, 0.12f, 0.25f), Point3D(0.0f, 0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(0.0f, 0.12f, -0.25f), Point3D(0.0f, 0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(0.0f, -0.12f, -0.25f), Point3D(0.0f, -0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(0.0f, -0.12f, 0.25f), Point3D(0.0f, -0.25f, 0.0f)));

    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, 0.25f), Point3D(-2.0f, -0.12f, 0.25f)));
    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, -0.25f), Point3D(-2.0f, -0.12f, -0.25f)));
    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, 0.25f), Point3D(-2.0f, 0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, -0.25f), Point3D(-2.0f, 0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(-2.0f, -0.12f, -0.25f), Point3D(-2.0f, -0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(-2.0f, -0.12f, 0.25f), Point3D(-2.0f, -0.25f, 0.0f)));

    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, 0.25f), Point3D(0.0f, 0.12f, 0.25f)));
    figure.push_back(Segment3D(Point3D(-2.0f, 0.12f, -0.25f), Point3D(0.0f, 0.12f, -0.25f)));
    figure.push_back(Segment3D(Point3D(-2.0f, 0.25f, 0.0f), Point3D(0.0f, 0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(-2.0f, -0.12f, -0.25f), Point3D(0.0f, -0.12f, -0.25f)));
    figure.push_back(Segment3D(Point3D(-2.0f, -0.25f, 0.0f), Point3D(0.0f, -0.25f, 0.0f)));
    figure.push_back(Segment3D(Point3D(-2.0f, -0.12f, 0.25f), Point3D(0.0f, -0.12f, 0.25f)));

	for (auto& segment : figure) {
		segment.point_a.x *= scale;
		segment.point_a.y *= scale;
		segment.point_a.z *= scale;

		segment.point_b.x *= scale;
		segment.point_b.y *= scale;
		segment.point_b.z *= scale;
	}
}
