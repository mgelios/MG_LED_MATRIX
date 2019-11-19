#include <Arduino.h>
#include <FastLED.h>

char snow_state[16][16];

void snowInit() {
    memset(snow_state, 0, sizeof(snow_state));
}

void snowAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 15; j++) {
            snow_state[i][j] = snow_state[i][j+1];
        }
    }
    for (int i = 0; i < 16; i++) {
        if (random(7) == 1) {
            snow_state[i][15] = random(2) + 1;
        } else {
            snow_state[i][15] = 0;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]] = 0;
            if (snow_state[i][j] == 1) {
                leds[translation[i][j]].setRGB(255,255,255);
            }
        }
    }
}