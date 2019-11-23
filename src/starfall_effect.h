#include <Arduino.h>
#include <FastLED.h>

signed char starfallVectorX[8] = {0,1,1,1,0,-1,-1,-1};
signed char starfallVectorY[8] = {1,1,0,-1,-1,-1,0,1};
signed char starfallPositionX[8] = {0,0,0,0,0,0,0,0};
signed char starfallInitPositionX[8] = {8,8,8,8,7,7,7,7};
signed char starfallPositionY[8] = {0,0,0,0,0,0,0,0};
signed char starfallInitPositionY[8] = {8,8,7,7,7,7,8,8};
bool active[8] = {0,0,0,0,0,0,0,0};

void starfallAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 256; i++) {
        leds[i].fadeToBlackBy(128);
    }
    for (int i = 0; i < 8; i++) {
        if (active[i]) {
            signed char nextCoordX = starfallPositionX[i] + starfallVectorX[i];
            signed char nextCoordY = starfallPositionY[i] + starfallVectorY[i];
            if (nextCoordX > 15 || nextCoordX < 0 || nextCoordY > 15 || nextCoordY < 0) {
                active[i] = false;
            } else {
                starfallPositionX[i] = nextCoordX;
                starfallPositionY[i] = nextCoordY;
                leds[translation[starfallPositionX[i]][starfallPositionY[i]]].setRGB(255, 255, 255);
            }
        } else {
            if (random(10) == 6) {
                active[i] = true;
                starfallPositionX[i] = starfallInitPositionX[i];
                starfallPositionY[i] = starfallInitPositionY[i];
                leds[translation[starfallPositionX[i]][starfallPositionY[i]]].setRGB(255, 255, 255);
            }
        }
    }
}