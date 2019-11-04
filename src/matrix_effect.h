#include <Arduino.h>
#include <FastLED.h>

uint32_t matrix_grad[6] = {0x000000, 0x002000, 0x004000, 0x008000, 0x00AF00, 0x00FF00};

char martix_points[16][16];

void matrixEffect(CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 15; j++) {
            martix_points[i][j] = martix_points[i][j + 1];
        }

    for (int i = 0; i < 16; i++) {
        if (random(13) == 1) {
            martix_points[i][15] = 5;
        } else {
            if (martix_points[i][14] > 0) {
                martix_points[i][15] = martix_points[i][14] - 1;
            } else {
                martix_points[i][15] = 0;
            }
        }
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]] = matrix_grad[martix_points[i][j]];
        }
    }
}