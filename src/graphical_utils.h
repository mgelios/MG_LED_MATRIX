#include <Arduino.h>
#include <FastLED.h>

struct DecimalVector {
    int xAxis;
    int yAxis;
    int scale;
};

struct DecimalPosition {
    int coordX;
    int coordY;
};