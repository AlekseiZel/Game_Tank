#pragma once

class Ball {
public:
    float x; 
    float y; 
    float radius; 
    float dx; 
    float dy; 
    bool is_sticky;
    bool is_stuck; 
    float dx_sticky;

    Ball(float x, float y, float radius, float dx, float dy);
    void draw(uint32_t buffer[][SCREEN_WIDTH]);
};

