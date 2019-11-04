#include <Arduino.h>
#include <FastLED.h>

short fire_energy[16][16];

CRGB colors[8] = {0x000000, 0x3F0000, 0x7F0000, 0xFF0000, 0xFF3F00, 0xFF7F00, 0xFFBF00, 0xFFFF00};

void fireInit() {
    memset(fire_energy, 0, sizeof(fire_energy));
}

void fireAnimation(CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int j = 15; j > 0; j--) {
        for (int i = 0; i < 16; i++)
            if (fire_energy[i][j-1] > 0) {
                fire_energy[i][j] = fire_energy[i][j-1] - random(fire_energy[i][j-1] / 2 + 1);
            }            
        }

    for (int i = 0; i < 16; i++) {
        fire_energy[i][0] = random(13) + 2;
    }

    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]] = colors[fire_energy[i][j]/2];
        }
}
