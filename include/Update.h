#pragma once
#include "Tank.h"
#include "Bullet.h"
#include "Box.h"
#include "Boom.h"
#include "Snowflake.h"
#include <vector>

void update(float dt, Tank& tank, std::vector<Snowflake>& snowflakes, std::vector<Box>& boxes, Box& target_box,
	std::vector<Bullet>& bullets, std::vector<Bullet>& enemy_bullets, std::vector<Boom>& booms,
	std::vector<Boom>& enemy_shot_booms, bool is_life, bool is_win);
