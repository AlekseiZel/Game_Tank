#include "Object3D.h"

Object3D::Object3D() : position(Point3D()), elevator_angle(0), dir_angle(0), scale(10), speed(10), color(0x00FF0000){

}

void Object3D::draw(uint32_t buffer[][SCREEN_WIDTH]) {
	for (auto& segment : absolut_figure) {
		segment.color = color;
		segment.draw(buffer);
	}
}