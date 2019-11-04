#include <Arduino.h>
#include <FastLED.h>

void hueAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]].setHSV(i + offset, 255, 255);
        }
}

void hueSmallAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 256; i++) {
        int color = offset + i;
        if (color > 255) {
            color = color - 256;
        }
        leds[i].setHSV(color, 255, 255);
    }
}