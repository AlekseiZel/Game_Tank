#include "Tank.h"
#include "Engine.h"
#include "Matrix.h"
#include "Point3D.h"
#include "Segment3D.h"
#include <vector>

#define pi (3.1415f)

Tank::Tank(){
		
    speed = 0.002f;
    scale = 13;
    color = 0x006400;
    chassi.color = color;
    turret.color = color;
    muzzle.color = color;

    // шасси
    chassi_point.push_back(Point3D(-5.0f, 2.5f, 0.0f));
    chassi_point.push_back(Point3D(5.0f, 2.5f, 0.0f));
    chassi_point.push_back(Point3D(5.0f, -2.5f, 0.0f));
    chassi_point.push_back(Point3D(-5.0f, -2.5f, 0.0f));

	chassi.figure.push_back(Segment3D(Point3D(-5.0f, 2.5f, 2.0f), Point3D(5.0f, 2.5f, 2.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-5.0f, -2.5f, 2.0f), Point3D(5.0f, -2.5f, 2.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-4.0f, 2.5f, 0.0f), Point3D(4.0f, 2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-4.0f, -2.5f, 0.0f), Point3D(4.0f, -2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-4.0f, 2.5f, 0.0f), Point3D(-4.0f, -2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(4.0f, 2.5f, 0.0f), Point3D(4.0f, -2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-5.0f, 2.5f, 2.0f), Point3D(-5.0f, -2.5f, 2.0f)));
    chassi.figure.push_back(Segment3D(Point3D(5.0f, 2.5f, 2.0f), Point3D(5.0f, -2.5f, 2.0f)));

    chassi.figure.push_back(Segment3D(Point3D(-5.0f, 2.5f, 2.0f), Point3D(-4.0f, 2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(-5.0f, -2.5f, 2.0f), Point3D(-4.0f, -2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(5.0f, 2.5f, 2.0f), Point3D(4.0f, 2.5f, 0.0f)));
    chassi.figure.push_back(Segment3D(Point3D(5.0f, -2.5f, 2.0f), Point3D(4.0f, -2.5f, 0.0f)));

    // башня
    turret.figure.push_back(Segment3D(Point3D(-1.5f, -0.5f, 3.5f), Point3D(-1.5f, 0.5f, 3.5f)));
    turret.figure.push_back(Segment3D(Point3D(1.5f, -0.5f, 3.5f), Point3D(1.5f, 0.5f, 3.5f)));
    turret.figure.push_back(Segment3D(Point3D(-1.5f, -0.5f, 3.5f), Point3D(0.0f, -1.0f, 3.5f)));
    turret.figure.push_back(Segment3D(Point3D(-1.5f, 0.5f, 3.5f), Point3D(0.0f, 1.0f, 3.5f)));
    turret.figure.push_back(Segment3D(Point3D(1.5f, -0.5f, 3.5f), Point3D(0.0f, -1.0f, 3.5f)));
    turret.figure.push_back(Segment3D(Point3D(1.5f, 0.5f, 3.5f), Point3D(0.0f, 1.0f, 3.5f)));

    turret.figure.push_back(Segment3D(Point3D(-2.5f, -1.0f, 2.0f), Point3D(-2.5f, 1.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(2.5f, -1.0f, 2.0f), Point3D(2.5f, 1.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(-2.5f, -1.0f, 2.0f), Point3D(0.0f, -2.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(-2.5f, 1.0f, 2.0f), Point3D(0.0f, 2.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(2.5f, -1.0f, 2.0f), Point3D(0.0f, -2.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(2.5f, 1.0f, 2.0f), Point3D(0.0f, 2.0f, 2.0f)));

    turret.figure.push_back(Segment3D(Point3D(0.0f, 1.0f, 3.5f), Point3D(0.0f, 2.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(0.0f, -1.0f, 3.5f), Point3D(0.0f, -2.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(-1.5f, -0.5f, 3.5f), Point3D(-2.5f, -1.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(-1.5f, 0.5f, 3.5f), Point3D(-2.5f, 1.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(1.5f, -0.5f, 3.5f), Point3D(2.5f, -1.0f, 2.0f)));
    turret.figure.push_back(Segment3D(Point3D(1.5f, 0.5f, 3.5f), Point3D(2.5f, 1.0f, 2.0f)));

    // дуло
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, 0.12f, 0.25f), Point3D(0.0f, -0.12f, 0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, 0.12f, -0.25f), Point3D(0.0f, -0.12f, -0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, 0.12f, 0.25f), Point3D(0.0f, 0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, 0.12f, -0.25f), Point3D(0.0f, 0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, -0.12f, -0.25f), Point3D(0.0f, -0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(0.0f, -0.12f, 0.25f), Point3D(0.0f, -0.25f, 0.0f)));

    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, 0.25f), Point3D(-4.0f, -0.12f, 0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, -0.25f), Point3D(-4.0f, -0.12f, -0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, 0.25f), Point3D(-4.0f, 0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, -0.25f), Point3D(-4.0f, 0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, -0.12f, -0.25f), Point3D(-4.0f, -0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, -0.12f, 0.25f), Point3D(-4.0f, -0.25f, 0.0f)));

    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, 0.25f), Point3D(0.0f, 0.12f, 0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.12f, -0.25f), Point3D(0.0f, 0.12f, -0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, 0.25f, 0.0f), Point3D(0.0f, 0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, -0.12f, -0.25f), Point3D(0.0f, -0.12f, -0.25f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, -0.25f, 0.0f), Point3D(0.0f, -0.25f, 0.0f)));
    muzzle.figure.push_back(Segment3D(Point3D(-4.0f, -0.12f, 0.25f), Point3D(0.0f, -0.12f, 0.25f)));


    for (auto& segment : chassi.figure) {
   
        segment.point_a.x *= scale;
        segment.point_a.y *= scale;
        segment.point_a.z *= scale;

        segment.point_b.x *= scale;
        segment.point_b.y *= scale;
        segment.point_b.z *= scale;
    }
    for (auto& point : chassi_point) {
        point.x *= scale;
        point.y *= scale;
        point.z *= scale;
    }

    for (auto& segment : turret.figure) {

        segment.point_a.x *= scale;
        segment.point_a.y *= scale;
        segment.point_a.z *= scale;

        segment.point_b.x *= scale;
        segment.point_b.y *= scale;
        segment.point_b.z *= scale;
    }


    for (auto& segment : muzzle.figure) {

        segment.point_a.x *= scale;
        segment.point_a.y *= scale;
        segment.point_a.z *= scale;

        segment.point_b.x *= scale;
        segment.point_b.y *= scale;
        segment.point_b.z *= scale;
    }
    Point3D move_muzzle(-2.0f * scale, 0.0f, 3.0f * scale);
        
    translationMatrix_muzzle = createTranslationMatrix(move_muzzle);
}

void Tank::moveForward(float dt) {
    Point3D move_dir(-1.0f, 0.0f, 0.0f);
    move_dir = move_dir.applyTransformation(createRotationMatrixZ(dir_angle));
    Point3D newP;
    newP.x = position.x + speed * 50 * dt * move_dir.x;
    newP.y = position.y + speed * 50 * dt * move_dir.y;
    newP.z = position.z;

    position.x = newP.x;
    position.y = newP.y;
    position.z = newP.z;
}

void Tank::moveBack(float dt) {
    Point3D move_dir(-1.0f, 0.0f, 0.0f);
    move_dir = move_dir.applyTransformation(createRotationMatrixZ(dir_angle));
    Point3D newP;
    newP.x = position.x - speed * 50 * dt * move_dir.x;
    newP.y = position.y - speed * 50 * dt * move_dir.y;
    newP.z = position.z;

    position.x = newP.x;
    position.y = newP.y;
    position.z = newP.z;
}

void Tank::turnTankLeft(float dt){
    float newA = dir_angle - speed * dt;

    if (newA >= -pi )
    {
        dir_angle = newA;
    }
    else
    {
        dir_angle = pi;
    }
}

void Tank::turnTankRight(float dt){
    float newA = dir_angle + speed * dt;

    if (newA <= pi)
    {
        dir_angle = newA;
    }
    else
    {
        dir_angle = -pi;
    }
}

void Tank::turnTurretLeft(float dt) {
    float newA = turret.dir_angle - speed * dt;

    if (newA >= -pi)
    {
        turret.dir_angle = newA;
    }
    else
    {
        turret.dir_angle = pi;
    }
}

void Tank::turnTurretRight(float dt) {
    float newA = turret.dir_angle + speed * dt;

    if (newA <= pi)
    {
        turret.dir_angle = newA;
    }
    else
    {
        turret.dir_angle = -pi;
    }
}

void Tank::upMuzzle(float dt) {
    float newA = muzzle.elevator_angle + speed * dt;

    if (newA < 0.8f)
    {
        muzzle.elevator_angle = newA;
    }
}

void Tank::downMuzzle(float dt) {
    float newA = muzzle.elevator_angle - speed * dt;

    if (newA > -0.2f)
    {
        muzzle.elevator_angle = newA;
    }
}



bool Tank::isPointInsideTopOfСhassi(const Point3D& point) {
    bool isInside = false;

    // попадание внутрь верхней части шасси по высоте
    if ((point.z < 2.0f * scale) && (point.z > 1.8f * scale)) {
        absolut_chassi_point.clear();
        Point3D absolut_point;
        for (auto& point : chassi_point) {

            absolut_point = point.applyTransformation(createRotationMatrixZ(dir_angle));
            absolut_point = absolut_point.applyTransformation(createTranslationMatrix(position));

            absolut_chassi_point.push_back(absolut_point);
        }
        // попадание в периметр шасси
        int n = absolut_chassi_point.size();
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((absolut_chassi_point[i].y > point.y) != (absolut_chassi_point[j].y > point.y)) &&
                (point.x < (absolut_chassi_point[j].x - absolut_chassi_point[i].x) * (point.y - absolut_chassi_point[i].y) /
                (absolut_chassi_point[j].y - absolut_chassi_point[i].y) + absolut_chassi_point[i].x)) {
                isInside = !isInside;
            }
        }
    }
    return isInside;
}

void Tank::draw(uint32_t buffer[][SCREEN_WIDTH])
{
    chassi.draw(buffer);
    turret.draw(buffer);
    muzzle.draw(buffer);
}