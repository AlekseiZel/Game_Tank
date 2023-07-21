#include "Engine.h"
#include "Segment3D.h"
#include <cmath>


Segment3D::Segment3D() : point_a(Point3D()), point_b(Point3D()), color(0x00FF0000) {}
Segment3D::Segment3D(const Point3D& a, const Point3D& b) : point_a(a), point_b(b), color(0x00FF0000) {}

void Segment3D::draw(uint32_t buffer[][SCREEN_WIDTH]) {
    // сдвиг, чтобы объекты отображались в центре экрана
    int offsetX = SCREEN_WIDTH / 2;
    int offsetY = SCREEN_HEIGHT / 2;

    // первая точка на экране
    float isoX = (point_a.x - point_a.y) + offsetX;
    float isoY = (point_a.z - (point_a.x + point_a.y) * 0.35f) + offsetY;
    int screenX_a = static_cast<int>(isoX);
    int screenY_a = static_cast<int>(isoY);
    screenY_a = SCREEN_HEIGHT - screenY_a;

    // вторая точка на экране
    isoX = (point_b.x - point_b.y) + offsetX;
    isoY = (point_b.z - (point_b.x + point_b.y) * 0.35f) + offsetY;
    int screenX_b = static_cast<int>(isoX);
    int screenY_b = static_cast<int>(isoY);
    screenY_b = SCREEN_HEIGHT - screenY_b;

    // отрезок между точками
    int dx = std::abs(screenX_b - screenX_a);
    int dy = std::abs(screenY_b - screenY_a);
    int sx = (screenX_a < screenX_b) ? 1 : -1;
    int sy = (screenY_a < screenY_b) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Проверяем, чтобы координаты были в пределах экрана
        if (screenX_a >= 0 && screenX_a < SCREEN_WIDTH && screenY_a >= 0 && screenY_a < SCREEN_HEIGHT) {
            buffer[screenY_a][screenX_a] = color;
        }

        if (screenX_a == screenX_b && screenY_a == screenY_b) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            screenX_a += sx;
        }
        if (e2 < dx) {
            err += dx;
            screenY_a += sy;
        }
    }
}