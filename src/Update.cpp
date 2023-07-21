#include "Update.h"
#include "Matrix.h"
#include "Point3D.h"
#include "Tank.h"
#include "Box.h"
#include "Boom.h"
#include "Engine.h"
#include "Segment3D.h"
#include "Snowflake.h"
#include <vector>
#include <random>

#define pi (3.1415f)

static float t = 1.f;
float t_shot = 5.f;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distribution(-400.0f, 400.0f);
std::uniform_real_distribution<float> dis(0.0f, 2 * pi); 

void update(float dt, Tank & tank, std::vector<Snowflake> & snowflakes, std::vector<Box>& boxes, Box & target_box,
        std::vector<Bullet> & bullets, std::vector<Bullet>& enemy_bullets, std::vector<Boom>& booms,
        std::vector<Boom>& enemy_shot_booms, bool is_life, bool is_win) {
    
    Segment3D absolut_segment;
    std::array<std::array<float, 4>, 4> curr_matrix;

    tank.chassi.absolut_figure.clear();
    tank.turret.absolut_figure.clear();
    tank.muzzle.absolut_figure.clear();
    tank.absolut_chassi_point.clear();
    
    // балистика снаряда
    for (auto& bullet : bullets) {
        if (bullet.position.z > 0) {
            bullet.position.x += bullet.direction.x * bullet.speed * dt;
            bullet.position.y += bullet.direction.y * bullet.speed * dt;
            bullet.position.z += bullet.direction.z * bullet.speed * dt;

            bullet.direction.z -= 0.6f * dt;
            bullet.elevator_angle -= 0.6f * dt;

            // снаряд коснулся земли
            if (bullet.position.z <= 0) {
                // взрыв
                Boom new_boom;
                new_boom.position.x = bullet.position.x;
                new_boom.position.y = bullet.position.y;
                booms.push_back(new_boom);

                // удаляем попавшие во взрыв снежинки
                auto isEven_kill_snowflake = [&bullet](Snowflake snowflake) {
                    return (snowflake.is_stuck && !snowflake.is_stuck_on_chassi) &&
                            (snowflake.position.x > bullet.position.x - 40.0f) &&
                            (snowflake.position.x < bullet.position.x + 40.0f)&&
                            (snowflake.position.y > bullet.position.y - 40.0f)&&
                            (snowflake.position.y < bullet.position.y + 40.0f); };

                snowflakes.erase(std::remove_if(snowflakes.begin(), snowflakes.end(), isEven_kill_snowflake), snowflakes.end());
            }
        }
    }
    // удаляем снаряды упавшие на землю
    auto isEven_bullet = [](Bullet bullet) { return bullet.position.z < 0; };
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), isEven_bullet), bullets.end());


    // балистика снаряда врага
    for (auto& enemy_bullet : enemy_bullets) {
        if (enemy_bullet.position.z > 0) {
            enemy_bullet.position.x += enemy_bullet.direction.x * enemy_bullet.speed * dt;
            enemy_bullet.position.y += enemy_bullet.direction.y * enemy_bullet.speed * dt;
        }
    }
    // удаляем снаряды врага улетевшие слишком далеко
    auto isEven_enemy_bullet = [](Bullet bullet) { return ((bullet.position.x < -800.f) ||
                                                            (bullet.position.x > 800.f) ||
                                                            (bullet.position.y < -800.f) ||
                                                            (bullet.position.y > 800.f)); };
    enemy_bullets.erase(std::remove_if(enemy_bullets.begin(), enemy_bullets.end(), isEven_enemy_bullet), enemy_bullets.end());


    //  расширение взрыва
    for (auto& boom : booms) {
        boom.scale += boom.speed * dt;

        boom.absolut_figure.clear();
        for (auto& segment : boom.figure) {
            absolut_segment.point_a.x = segment.point_a.x * boom.scale;
            absolut_segment.point_a.y = segment.point_a.y * boom.scale;
            absolut_segment.point_b.x = segment.point_b.x * boom.scale;
            absolut_segment.point_b.y = segment.point_b.y * boom.scale;

            absolut_segment.point_a = absolut_segment.point_a.applyTransformation(createTranslationMatrix(boom.position));
            absolut_segment.point_b = absolut_segment.point_b.applyTransformation(createTranslationMatrix(boom.position));

            boom.absolut_figure.push_back(absolut_segment);
        }
    }
    // удаляем взрывы
    auto isEven_boom = [](Boom boom) { return boom.scale > 10; };
    booms.erase(std::remove_if(booms.begin(), booms.end(), isEven_boom), booms.end());


    //  обратный взрыв при выстреле врага
    for (auto& enemy_shot_boom : enemy_shot_booms) {
        enemy_shot_boom.scale -= enemy_shot_boom.speed * dt;

        enemy_shot_boom.absolut_figure.clear();
        for (auto& segment : enemy_shot_boom.figure) {
            absolut_segment.point_a.x = segment.point_a.x * enemy_shot_boom.scale;
            absolut_segment.point_a.y = segment.point_a.y * enemy_shot_boom.scale;
            absolut_segment.point_a.z = segment.point_a.z;
            absolut_segment.point_b.x = segment.point_b.x * enemy_shot_boom.scale;
            absolut_segment.point_b.y = segment.point_b.y * enemy_shot_boom.scale;
            absolut_segment.point_b.z = segment.point_b.z;

            absolut_segment.point_a = absolut_segment.point_a.applyTransformation(createTranslationMatrix(enemy_shot_boom.position));
            absolut_segment.point_b = absolut_segment.point_b.applyTransformation(createTranslationMatrix(enemy_shot_boom.position));

            enemy_shot_boom.absolut_figure.push_back(absolut_segment);
        }
        // взрыв схлопнулся запускаем снаряд в произвольном направлении
        if (enemy_shot_boom.scale < 3) {
            Bullet new_bullet;

            new_bullet.position = enemy_shot_boom.position;

            new_bullet.color = 0xFFFF00;
            new_bullet.speed = 80.f;

            // Генерируем случайный угол выстрела от 0 до 360
            new_bullet.dir_angle = dis(gen);

            new_bullet.direction = new_bullet.direction.applyTransformation(createRotationMatrixZ(new_bullet.dir_angle));
            enemy_bullets.push_back(new_bullet);
        }
    }
    // удаляем обратный взрыв при выстреле врага
    auto isEven_enemy_shot_boom = [](Boom enemy_shot_boom) { return enemy_shot_boom.scale < 3; };
    enemy_shot_booms.erase(std::remove_if(enemy_shot_booms.begin(), enemy_shot_booms.end(), isEven_enemy_shot_boom), enemy_shot_booms.end());


    // рисуем целевой блок на своей позиции
    // ставим на позицию и слегка доворачиваем для красоты
    curr_matrix = matrixMultiplication(createTranslationMatrix(target_box.position),
        createRotationMatrixZ(0.08f));
    target_box.absolut_figure.clear();
    for (auto& segment : target_box.figure) {
        absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
        absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

        target_box.absolut_figure.push_back(absolut_segment);
    }

    // рисуем блоки на своих позициях
    for (auto& box : boxes) {
        // ставим на позицию и слегка доворачиваем для красоты
        curr_matrix = matrixMultiplication(createTranslationMatrix(box.position),
                                            createRotationMatrixZ(0.08f));
        box.absolut_figure.clear();
        for (auto& segment : box.figure) {
            absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
            absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

            box.absolut_figure.push_back(absolut_segment);
        }
    }
    

    for (auto& bullet : bullets) {
        // поворачиваем и перемещаем снаряд
        curr_matrix = matrixMultiplication(createRotationMatrixZ(bullet.dir_angle),
                                            createRotationMatrixY(bullet.elevator_angle));
        curr_matrix = matrixMultiplication(createTranslationMatrix(bullet.position), curr_matrix);

        bullet.absolut_figure.clear();
        for (auto& segment : bullet.figure) {
            absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
            absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

            bullet.absolut_figure.push_back(absolut_segment);
        }   
    }

    for (auto& enemy_bullet : enemy_bullets) {
        // поворачиваем и перемещаем снаряд врага
        curr_matrix = matrixMultiplication(createTranslationMatrix(enemy_bullet.position),
                                            createRotationMatrixZ(enemy_bullet.dir_angle));

        enemy_bullet.absolut_figure.clear();
        for (auto& segment : enemy_bullet.figure) {
            absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
            absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

            enemy_bullet.absolut_figure.push_back(absolut_segment);
        }
    }


    // поворачиваем и перемещаем танк
    curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position), 
                                        createRotationMatrixZ(tank.dir_angle));
 
    for (auto& segment : tank.chassi.figure) {
        absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
        absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

        tank.chassi.absolut_figure.push_back(absolut_segment);
    }
    for (auto& point : tank.chassi_point) {
        Point3D absolut_point;
        absolut_point = point.applyTransformation(curr_matrix);

        tank.absolut_chassi_point.push_back(absolut_point);
    }

    // поворачиваем и перемещаем башню
    curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position),
                                        createRotationMatrixZ(tank.turret.dir_angle));
    for (auto& segment : tank.turret.figure) {
        absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
        absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

        tank.turret.absolut_figure.push_back(absolut_segment);
    }

    // поднимаем и перемещаем дуло, затем поворачиваем с башней, затем перемещаем с танком
    curr_matrix = matrixMultiplication(tank.translationMatrix_muzzle, 
                                        createRotationMatrixY(tank.muzzle.elevator_angle));
    curr_matrix = matrixMultiplication(createRotationMatrixZ(tank.turret.dir_angle), curr_matrix);
    curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position), curr_matrix);

    
    for (auto& segment : tank.muzzle.figure) {
        absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
        absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

        tank.muzzle.absolut_figure.push_back(absolut_segment);
    }

    // случайная коробка стреляет в случайном направлении
    t_shot -= dt;
    if (t_shot < 0) {
        t_shot = 1.f;
        
        if (boxes.size()) {
            std::uniform_int_distribution<> dist(0, boxes.size() - 1);
            int random_index = dist(gen);

            if (boxes[random_index].color != 0xFF00FF00) {
                Boom new_enemy_start_boom;
                new_enemy_start_boom.scale = 10.f;
                new_enemy_start_boom.speed = 10.f;
                new_enemy_start_boom.color = 0xFFFF00;
                new_enemy_start_boom.position.x = boxes[random_index].position.x + boxes[random_index].scale / 2;
                new_enemy_start_boom.position.y = boxes[random_index].position.y + boxes[random_index].scale / 2;
                new_enemy_start_boom.position.z = 30.f;

                enemy_shot_booms.push_back(new_enemy_start_boom);
            }
        }
    }

    // каждую секунду появляется новая снежинка
    t -= dt;
    if (t < 0) {
        t = 1.f;

        if (snowflakes.size() < 100) {
            Snowflake new_snowflake;
            // генератор случайных позиций снежинок
            new_snowflake.position.x = distribution(gen); 
            new_snowflake.position.y = distribution(gen);
            new_snowflake.position.z = 400;

            snowflakes.push_back(new_snowflake);
        }
    }

    for (auto& snowflake : snowflakes) {
        if (!snowflake.is_stuck) {

            // снежинка падает и вращается
            snowflake.position.z -= snowflake.speed * 50 * dt;

            snowflake.dir_angle += snowflake.speed * dt;
            if (snowflake.dir_angle >= pi)
            {
                snowflake.dir_angle = -pi;
            }

            // снежинка попала на шасси танка
            if (tank.isPointInsideTopOfСhassi(snowflake.position)) {
                snowflake.is_stuck = true;
                snowflake.is_stuck_on_chassi = true;
              
                // вычисляем коорлинаты снежинки относительно танка
                curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position),
                                                    createRotationMatrixZ(tank.dir_angle));

                curr_matrix = createInverseTransformationMatrix(curr_matrix);
                snowflake.position_on_chassi = snowflake.position.applyTransformation(curr_matrix);

                // доворачиваем до горизонта
                snowflake.dir_angle = 0.f;
                snowflake.elevator_angle = pi / 2;
            }

            // снежинка долетела до земли
            if (snowflake.position.z <= 0) {
                snowflake.is_stuck = true;
                snowflake.position.z = 0;

                // доворачиваем до горизонта
                snowflake.elevator_angle = pi / 2;
            }
        }

        snowflake.absolut_figure.clear();
        // снежинка не прилипла к танку
        if (!snowflake.is_stuck_on_chassi) {

            curr_matrix = matrixMultiplication(createRotationMatrixZ(snowflake.dir_angle),
                                                    createRotationMatrixY(snowflake.elevator_angle));

            curr_matrix = matrixMultiplication(createTranslationMatrix(snowflake.position), curr_matrix);
          
            for (auto& segment : snowflake.figure) {
                absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
                absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

                snowflake.absolut_figure.push_back(absolut_segment);
            }
        }
        else {
            // снежинка ездит на шасси танка
            for (auto& segment : snowflake.figure) {

                // поднимаем и перемещаем дуло, затем поворачиваем с башней, затем перемещаем с танком
                curr_matrix = matrixMultiplication(createTranslationMatrix(snowflake.position_on_chassi),
                                                    createRotationMatrixY(snowflake.elevator_angle));

                curr_matrix = matrixMultiplication(createRotationMatrixZ(tank.dir_angle), curr_matrix);
                curr_matrix = matrixMultiplication(createTranslationMatrix(tank.position), curr_matrix);


                absolut_segment.point_a = segment.point_a.applyTransformation(curr_matrix);
                absolut_segment.point_b = segment.point_b.applyTransformation(curr_matrix);

                snowflake.absolut_figure.push_back(absolut_segment);
            }
        }
    }

    // проверяем колизии

    // попадание снаряда в бокс
    for (auto& bullet : bullets) {
        for (auto it = boxes.begin(); it != boxes.end(); ++it) {
            Box& box = *it;
            if (box.isPointInsideOfBox(bullet.position)) {
                boxes.erase(it);
                break;
            }
        }   
    }

    // попадание снаряда врага в танк
    for (auto& enemy_bullet : enemy_bullets) {
        Point3D point = enemy_bullet.position;
        
        // поднимаем точку до плоскости обнаружения колизий с танком
        point.z = 1.9f * tank.scale;
        if(tank.isPointInsideTopOfСhassi(point)){
            if (!is_win) {
                // проигрыш
                tank.color = 0x00FF0000;
                tank.chassi.color = tank.color;
                tank.turret.color = tank.color;
                tank.muzzle.color = tank.color;
            }
        }
    }
    
    // наезд танка на бокс-врага
    for (auto& box : boxes) {
        for (auto& point : tank.absolut_chassi_point) {
            if (box.isPointInsideOfBox(point)) {
                if (!is_win) {
                    // проигрыш
                    tank.color = 0x00FF0000;
                    tank.chassi.color = tank.color;
                    tank.turret.color = tank.color;
                    tank.muzzle.color = tank.color;
                }
            }
        }
    }
    // наезд на целевой бокс
    for (auto& point : tank.absolut_chassi_point) {
        if (target_box.isPointInsideOfBox(point)) {
            if (is_life) {
                // выигрыш
                tank.color = 0xFF00FF00;
                tank.chassi.color = tank.color;
                tank.turret.color = tank.color;
                tank.muzzle.color = tank.color;
            }
        }
    }
}