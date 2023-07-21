#include "Engine.h"
#include "Block.h"
#include "Arcanoid.h"


Block::Block(float x, float y, float width, float height, uint32_t color) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->color = color;
    }

    void Block::draw(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {
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
                buffer[row][col] = color;
            }
        }
    }



