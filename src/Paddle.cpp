#include "Paddle.h"
#include "Engine.h"



Paddle::Paddle(int x, int y, int width, int height, int speed)
    : x(x), y(y), width(width), height(height), speed(speed), is_long(false), timer_long(0.f)
{
}

void Paddle::moveLeft(float dt)
{
    float newX = x - speed * dt;

    // Проверка границы экрана слева
    if (newX >= 0)
    {
        x = newX;
    }
    else
    {
        x = 0; 
    }
}

void Paddle::moveRight(float dt)
{
    float newX = x + speed * dt;

    // Проверка границы экрана справа
    if (newX + width <= SCREEN_WIDTH)
    {
        x = newX;
    }
    else
    {
        x = SCREEN_WIDTH - width; 
    }
}



void Paddle::draw(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    int startX = static_cast<int>(x);
    int startY = static_cast<int>(y);
    int endX = startX + static_cast<int>(width);
    int endY = startY + static_cast<int>(height);

    // Проверяем границы блока, чтобы не выходить за пределы экрана
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= SCREEN_WIDTH) endX = SCREEN_WIDTH - 1;
    if (endY >= SCREEN_HEIGHT) endY = SCREEN_HEIGHT - 1;

    for (int row = startY; row <= endY; row++) {
        for (int col = startX; col <= endX; col++) {
            buffer[row][col] = 0x804000; // коричневый
        }
    }
}