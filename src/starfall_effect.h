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

DecimalVector vectors[10] = {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};
DecimalPosition positions[10] = {{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10},{0,0,10}};
bool isStarActive[10] = {0,0,0,0,0,0,0,0,0,0};

void updatedStarfallAnimation(int offset, CRGB (&leds)[256], unsigned char (&translation)[16][16]) {
    for (int i = 0; i < 256; i++) {
        leds[i].fadeToBlackBy(128);
    }
    for (int i = 0; i < 10; i++) {
        if (isStarActive[i]) {
            DecimalPosition nextPosition = getNextDecimalPosition(positions[i], vectors[i]);
            if (nextPosition.coordX / nextPosition.scale < 0 || nextPosition.coordY / nextPosition.scale < 0 ||
                nextPosition.coordX /nextPosition.scale > 15 || nextPosition.coordY / nextPosition.scale > 15) {
                isStarActive[i] = false;
            } else {
                positions[i] = nextPosition;
                leds[translation[positions[i].coordX / positions[i].scale][positions[i].coordY / positions[i].scale]].setRGB(255, 255, 255);
            }
        } else {
            if (random(10) == 6) {
                positions[i].coordX = (random(2) + 7) * 10;
                positions[i].coordY = (random(2) + 7) * 10;
                positions[i].scale = 10;

                if (positions[i].coordX == 80 && positions[i].coordY == 80) {
                    vectors[i] = getVectorByLengthAndAngle(1, random(90), 10);
                } else if (positions[i].coordX == 70 && positions[i].coordY == 80) {
                    vectors[i] = getVectorByLengthAndAngle(1, random(90) + 90, 10);
                } else if (positions[i].coordX == 70 && positions[i].coordY == 70) {
                    vectors[i] = getVectorByLengthAndAngle(1, random(90) + 180, 10);
                } else {
                    vectors[i] = getVectorByLengthAndAngle(1, random(90) + 270, 10);
                }

                //vectors[i].xAxis = positions[i].coordX == 80 ? random(10) + 1 : -(random(10) + 1);
                //vectors[i].yAxis = positions[i].coordY == 80 ? random(10) + 1 : -(random(10) + 1);
                leds[translation[positions[i].coordX / positions[i].scale][positions[i].coordY / positions[i].scale]].setRGB(255, 255, 255);
                isStarActive[i] = true;
            }
        }
    }
}