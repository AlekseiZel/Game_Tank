#pragma once
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
#include <vector>


void update_Arcanoid(float dt, Paddle& paddle, std::vector<Block>& blocks, std::vector<Ball>& balls);