#pragma once
#include "Engine.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Object3D.h"
#include <vector>
#include <array>


class Tank : public Object3D {
public:

	Object3D chassi;
	Object3D turret;
	Object3D muzzle;
	std::array<std::array<float, 4>, 4> translationMatrix_muzzle;
	std::vector<Point3D> chassi_point;
	std::vector<Point3D> absolut_chassi_point;

	Tank();
	void moveForward(float dt);
	void moveBack(float dt);
	void turnTankLeft(float dt);
	void turnTankRight(float dt);
	void turnTurretLeft(float dt);
	void turnTurretRight(float dt);
	void upMuzzle(float dt);
	void downMuzzle(float dt);
	bool isPointInsideTopOfСhassi(const Point3D& point);
	void draw(uint32_t buffer[][SCREEN_WIDTH]);
};