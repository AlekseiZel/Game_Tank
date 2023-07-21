#include "Engine.h"
#include "Ball.h"
#include <algorithm>
#include <cmath>



Ball::Ball(float x, float y, float radius, float dx, float dy) {
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->dx = dx;
        this->dy = dy;
        this->is_sticky = false;
        this->is_stuck = false;
        this->dx_sticky = 0;
    }

void Ball::draw(uint32_t buffer[][SCREEN_WIDTH])
    {
        int x0 = static_cast<int>(x - radius);
        int y0 = static_cast<int>(y - radius);
        int x1 = static_cast<int>(x + radius);
        int y1 = static_cast<int>(y + radius);

        // Ограничение координат мяча, чтобы не выходил за границы экрана
        x0 = std::max(0, x0);
        y0 = std::max(0, y0);
        x1 = std::min(SCREEN_WIDTH - 1, x1);
        y1 = std::min(SCREEN_HEIGHT - 1, y1);

        for (int y = y0; y <= y1; y++)
        {
            for (int x = x0; x <= x1; x++)
            {
                float dx = static_cast<float>(x) - this->x;
                float dy = static_cast<float>(y) - this->y;
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance <= radius)
                {
                    buffer[y][x] = 0xFF00FF00; 
                }
            }
        }
    }
