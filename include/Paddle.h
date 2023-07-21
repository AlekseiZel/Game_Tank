#pragma once
#include "Engine.h"

class Paddle {
public:
    int x; 
    int y; 
    int width; 
    int height; 
    int speed;
    bool is_long;
    float timer_long;

    Paddle(int x, int y, int width, int height, int speed);
    void moveLeft(float dt);
    void moveRight(float dt);
    void draw(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
};