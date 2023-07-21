#include "Engine.h"
#include "EndOfGame.h"
#include "Matrix.h"
#include "Point3D.h"
#include "Segment3D.h"
#include "Snowflake.h"
#include "Box.h"
#include "Boom.h"
#include "Bullet.h"
#include "Update.h"
#include "Tank.h"
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include <random>

Tank tank;
std::vector<Snowflake> snowflakes;
std::vector<Box> boxes;
Box target_box;
std::vector<Bullet> bullets;
std::vector<Bullet> enemy_bullets;
std::vector<Boom> booms;
std::vector<Boom> enemy_sthot_booms;

bool is_life;
bool is_win;

float t = 0;
float delta_time_SPACE = 0;

void initialize()
{
    is_life = true;
    is_win = false;

    tank.color = 0x006400;
    tank.chassi.color = tank.color;
    tank.turret.color = tank.color;
    tank.muzzle.color = tank.color;
    tank.position.x = 160;
    tank.position.y = 500;

    snowflakes.clear();
    boxes.clear();
    bullets.clear();
    enemy_bullets.clear();
    booms.clear();
    enemy_sthot_booms.clear();

    // целевой зеленый блок
    target_box.color = 0xFF00FF00;
    target_box.position.x = -50;
    target_box.position.y = -450;

    // Устанавливаем seed для генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int lenght_side = 8;
    for (int i = 0; i < 7; i++) {
        Box new_box;
        // Генерируем случайные координаты блоков
        new_box.position.x = ((std::rand() % lenght_side) - lenght_side / 2) * new_box.scale * 1.3f;
        new_box.position.y = ((std::rand() % lenght_side) - lenght_side / 2) * new_box.scale * 1.3f;
        new_box.position.z = 0.f;

        boxes.push_back(new_box);
    }
}


void act(float dt)
{
    t += dt;
    delta_time_SPACE += dt;

    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();
    
    if (is_key_pressed('W')) {
        tank.moveForward(1.f);
    }

    if (is_key_pressed('S')) {
        tank.moveBack(1.f);
    }

    if (is_key_pressed('A')) {
        tank.turnTankLeft(1.f);
    }

    if (is_key_pressed('D')) {
        tank.turnTankRight(1.f);
    }

    if (is_key_pressed(VK_LEFT)) {
        tank.turnTurretLeft(1.f);
    }

    if (is_key_pressed(VK_RIGHT)) {
        tank.turnTurretRight(1.f);
    }

    if (is_key_pressed(VK_UP)) {
        tank.upMuzzle(1.f);
    }

    if (is_key_pressed(VK_DOWN)) {
        tank.downMuzzle(1.f);
    }

    if (is_key_pressed(VK_SPACE)) {

        // стреляем
        // задержка чтобы на одно нажатие появлялся один снаряд
        if (delta_time_SPACE > 0.2) {
            delta_time_SPACE = 0;
            Bullet new_bullet;
            Point3D tip_of_bullet(-tank.scale * 4.0f, 0.0f, 0.0f);
            std::array<std::array<float, 4>, 4> curr_matrix;
            // определяем стартовое положение снаряда
            // поднимаем и перемещаем дуло, затем поворачиваем с башней, затем перемещаем с танком
            curr_matrix = matrixMultiplication(createRotationMatrixY(tank.muzzle.elevator_angle),
                                                createTranslationMatrix(tip_of_bullet));
            curr_matrix = matrixMultiplication(tank.translationMatrix_muzzle, curr_matrix);
            curr_matrix = matrixMultiplication(createRotationMatrixZ(tank.turret.dir_angle), curr_matrix);
            curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position), curr_matrix);

            new_bullet.position = new_bullet.direction.applyTransformation(curr_matrix);

            // определяем направление снаряда по дулу танка
            new_bullet.elevator_angle = tank.muzzle.elevator_angle;
            new_bullet.dir_angle = tank.turret.dir_angle;

            curr_matrix = matrixMultiplication(createRotationMatrixZ(tank.turret.dir_angle),
                                                createRotationMatrixY(tank.muzzle.elevator_angle));
                                                   
            new_bullet.direction = new_bullet.direction.applyTransformation(curr_matrix);

            bullets.push_back(new_bullet);
        }

        if (!is_life || is_win) {
            // рестарт игры
            initialize();
            t = 0;
        } 
    }
      
    update(dt, tank, snowflakes, boxes, target_box, bullets, enemy_bullets, booms, enemy_sthot_booms, is_life, is_win);
 
    if (tank.color == 0x00FF0000) {
        is_life = false;
    }
    if (tank.color == 0xFF00FF00) {
        is_win = true;
    }
}


// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] RGB
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    buffer[10][10] = 0xFFFFFFFF;

    target_box.draw(buffer);

    for (auto& box : boxes) {
        box.draw(buffer);
    }
    for (auto& bullet : bullets) {
        bullet.draw(buffer);
    }

    for (auto& enemy_bullet : enemy_bullets) {
        enemy_bullet.draw(buffer);
    }

    for (auto & snowflake : snowflakes) {
        if (snowflake.is_stuck) {
            snowflake.draw(buffer);
        }      
    }

    for (auto & boom : booms) {
        boom.draw(buffer);
    }

    for (auto& enemy_sthot_boom : enemy_sthot_booms) {
        enemy_sthot_boom.draw(buffer);
    }
    
    tank.draw(buffer);
    for (auto & snowflake : snowflakes) {
        if (!snowflake.is_stuck) {
            snowflake.draw(buffer);
        }      
    }

    // проигрыш
    if (!is_life) {
        draw_Lose(buffer, 300, 200, 400);
    }
    // победа
    if (is_win) {
        draw_Win(buffer, 300, 200, 400);
    }
}


