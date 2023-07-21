#include "Arcanoid.h"
#include "Paddle.h"
#include "Block.h"
#include "Ball.h"
#include <vector>


void update_Arcanoid(float dt, Paddle& paddle, std::vector<Block>& blocks, std::vector<Ball>& balls) {
    std::vector<Ball> new_balls;

    if (paddle.is_long) {
        paddle.timer_long -= 0.01;
        if (paddle.timer_long < 0) {
            paddle.is_long = false;
            paddle.width /= 1.5;
        }
    }

    for (auto it_ball = balls.begin(); it_ball != balls.end(); ++it_ball) {
        Ball& ball = *it_ball;

        
        if (!ball.is_stuck) {
            ball.x += ball.dx * dt;
            ball.y += ball.dy * dt;
        }
        else {
            ball.x = paddle.x + paddle.width / 2 + ball.dx_sticky;
            ball.y = paddle.y - balls[0].radius;
        }

        // Проверка столкновения с границами экрана
        if (ball.x - ball.radius < 0) {
            ball.x = ball.radius;
            ball.dx = -ball.dx;
        }
        else if (ball.x + ball.radius > SCREEN_WIDTH) {
            ball.x = SCREEN_WIDTH - ball.radius;
            ball.dx = -ball.dx;
        }
        if (ball.y - ball.radius < 0) {
            ball.y = ball.radius;
            ball.dy = -ball.dy;
        }
        else if (ball.y + ball.radius > SCREEN_HEIGHT) {
            // Мяч достиг нижней границы экрана
            it_ball = balls.erase(it_ball);
            if (it_ball == balls.end()) {
                break;
            }
            continue;
        }

        // Проверка столкновения с платформой
        if (!ball.is_stuck) {
            if (ball.y + ball.radius >= paddle.y && ball.y - ball.radius <= paddle.y + paddle.height &&
                ball.x + ball.radius >= paddle.x && ball.x - ball.radius <= paddle.x + paddle.width) {

                float paddleCenterX = paddle.x + paddle.width / 2.0f;
                float deviation = ball.x - paddleCenterX;

                ball.dx = deviation * 0.01f;
                ball.dy = -ball.dy;
                if (ball.is_sticky) {
                    ball.is_sticky = false;
                    ball.is_stuck = true;
                    ball.dx_sticky = deviation;
                }
            }
        }

        // Проверка столкновения с блоками
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            Block& block = *it;

            if (ball.y + ball.radius >= block.y &&
                ball.y - ball.radius <= block.y + block.height &&
                ball.x + ball.radius >= block.x &&
                ball.x - ball.radius <= block.x + block.width) {

                bool fromLeft = ball.x < block.x;
                bool fromRight = ball.x > block.x + block.width;
                bool fromTop = ball.y < block.y;
                bool fromBottom = ball.y > block.y + block.height;

                if (fromLeft || fromRight) {
                    ball.dx = -ball.dx;
                }
                if (fromTop || fromBottom) {
                    ball.dy = -ball.dy;
                }
                
                // на темно фиолетовом блоке будет длинная платформа
                if (block.color == 0x00800080) {
                    if (!paddle.is_long) {
                        paddle.is_long = true;
                        paddle.width *= 1.5;
                    }
                    paddle.timer_long = 50.f;
                    
                }

                // на розовом блоке будет прилипание
                if (block.color == 0x00FF0080) {
                    ball.is_sticky = true;
                }

                // на светло фиолетовом блоке будет появлятся дополнительный мяч
                if (block.color == 0x8080FF) {
                    Ball new_ball(ball.x, ball.y, 15, -1.f, -1.f);
                    new_balls.push_back(new_ball);
                }

                blocks.erase(it);
                break;
            }
        }
    }
    for (auto & ball : new_balls) {
        balls.push_back(ball);
    }
}

