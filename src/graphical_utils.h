#include <Arduino.h>
#include <FastLED.h>

struct DecimalVector {
    int xAxis;
    int yAxis;
};

struct DecimalPosition {
    int coordX;
    int coordY;
    int scale;
};

DecimalPosition getNextDecimalPosition(DecimalPosition position, DecimalVector vector) {
    position.coordX += vector.xAxis;
    position.coordY += vector.yAxis;
    return position;
}