#include <Arduino.h>
#include <FastLED.h>

signed char vectorX[4] = {1,-1,1,1};
signed char vectorY[4] = {1,1,-1,1};
signed char positionX[4] = {3,11,0,0};
signed char positionY[4] = {0,0,5,7};
char ballColor[4] = {48, 96, 144, 192};

void ballsAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 256; i++) {
        leds[i].fadeToBlackBy(128);
    }

    for (int i = 0; i < 4; i++) {
        if ((positionX[i] == 0 && vectorX[i] < 0) || (positionX[i] == 15 && vectorX[i] > 0)) {
            vectorX[i] = -vectorX[i];
        }
        if ((positionY[i] == 0 && vectorY[i] < 0) || (positionY[i] == 15 && vectorY[i] > 0)) {
            vectorY[i] = -vectorY[i];
        }
        positionX[i] = positionX[i] + vectorX[i];
        positionY[i] = positionY[i] + vectorY[i];
        leds[translation[positionX[i]][positionY[i]]].setHSV(ballColor[i], 255, 255);
        ballColor[i] += 1;  
    }
}