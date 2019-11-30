#include <Arduino.h>
#include <FastLED.h>
#include <math.h>

struct DecimalVector {
    int xAxis;
    int yAxis;
};

struct DecimalPosition {
    int coordX;
    int coordY;
    int scale;
};

DecimalVector getVectorByLengthAndAngle(int length, int degree, int multiplier) {
    double sinValue = sin(degree * PI / 180);
    double cosValue = cos(degree * PI / 180);
    int xAxis = trunc((cosValue * length) * multiplier);
    int yAxis = trunc((sinValue * length) * multiplier);
    return {xAxis, yAxis};
}

DecimalPosition getNextDecimalPosition(DecimalPosition position, DecimalVector vector) {
    position.coordX += vector.xAxis;
    position.coordY += vector.yAxis;
    return position;
}