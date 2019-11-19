#include <Arduino.h>
#include <FastLED.h>

#include <state.h>
#include <fire_effect.h>
#include <matrix_effect.h>
#include <hue_effect.h>
#include <balls_effect.h>
#include <snow_effect.h>

#define DATA_PIN    4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

void setup() {
    delay(1000);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, 256).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(31);
    fireInit();
    snowInit();
}

void randomBlinks() {
    for (int i = 0; i < 256; i++) {
        leds[i].fadeToBlackBy(64);
    }
    for (int i = 0; i < 256; i++) {
        if (random(32) == 1) {
            leds[i].setHSV(random(256), 255,255);
        }
    }
}

void loop() {
    int offset = 239;
    while (true) {
        //fireAnimation(leds, translation);
        //hueAnimation(offset, leds, translation);
        //hueSmallAnimation(offset, leds, translation);
        //randomBlinks();
        //ballsAnimation(offset, leds, translation);
        //matrixEffect(leds, translation);
        snowAnimation(offset, leds, translation);
        FastLED.show();
        delay(300);
        offset--;
        if (offset < 0) offset = 239;
    }
}
