#include <Arduino.h>
#include <FastLED.h>

#include <fire_effect.h>

#define DATA_PIN    4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

void setup() {
    delay(1000);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, 256).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(16);
    fireInit();
}

void hueAnimation(int offset) {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]].setHSV(i + offset, 255, 255);
        }
}

void hueSmallAnimation(int offset) {
    for (int i = 0; i < 256; i++) {
        int color = offset + i;
        if (color > 255) {
            color = color - 256;
        }
        leds[i].setHSV(color, 255, 255);
    }
}

void randomBlinks() {
    for (int i = 0; i < 256; i++) {
        leds[i].setHSV(random(256), 255,255);
    }
}

uint32_t matrix_grad[4] = {0x000000, 0x002000, 0x008000, 0x00FF00};

char martix_points[16][16];

void matrixEffect() {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 15; j++) {
            martix_points[i][j] = martix_points[i][j + 1];
        }

    for (int i = 0; i < 16; i++) {
        if (random(10) == 1) {
            martix_points[i][15] = 3;
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

void loop() {
    int offset = 239;
    while (true) {
        fireAnimation();
        //hueAnimation(offset);
        //hueSmallAnimation(offset);
        //randomBlinks();
        //matrixEffect();
        FastLED.show();
        delay(100);
        offset--;
        if (offset < 0) offset = 239;
    }
}
