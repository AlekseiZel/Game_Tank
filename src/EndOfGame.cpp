#include "EndOfGame.h"
#include <vector>

void draw_Win(uint32_t buffer[][SCREEN_WIDTH], int x, int y, int size) {
    // Определение координат пикселей для символа "V"
    int points[][2] = {
        {x, y},
        {x + size / 2, y + size},
        {x + size, y},
        {x + size / 2, y + size / 2},
        {x, y}
    };

    for (int i = 0; i < sizeof(points) / sizeof(points[0]) - 1; ++i) {
        int x0 = points[i][0];
        int y0 = points[i][1];
        int x1 = points[i + 1][0];
        int y1 = points[i + 1][1];

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            buffer[y0][x0] = 0xFF00FF00;

            if (x0 == x1 && y0 == y1) {
                break;
            }

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
}

void draw_Lose(uint32_t buffer[][SCREEN_WIDTH], int x, int y, int size) {
    // Определение координат пикселей для символа "X"
    int points[][2] = {
        {x, y},
        {x + size, y + size},
        {x, y + size},
        {x + size, y}
    };

    for (int i = 0; i < sizeof(points) / sizeof(points[0]); ++i) {
        int x0 = points[i][0];
        int y0 = points[i][1];
        int x1 = points[(i + 1) % (sizeof(points) / sizeof(points[0]))][0];
        int y1 = points[(i + 1) % (sizeof(points) / sizeof(points[0]))][1];

        if (y0 != y1) {
            int dx = abs(x1 - x0);
            int dy = abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            while (true) {
                buffer[y0][x0] = 0x00FF0000;

                if (x0 == x1 && y0 == y1) {
                    break;
                }

                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y0 += sy;
                }
            }
        }
    }
}
