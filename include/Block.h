#pragma once
#include "Engine.h"
class Block {
public:
    float x; 
    float y; 
    float width; 
    float height; 
    uint32_t color;

    Block(float x, float y, float width, float height, uint32_t color);
    void draw(uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH]);
};