#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN    4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[256];
CRGB colors[8] = {CRGB::Black, CRGB::Maroon, CRGB::DarkRed, CRGB::Red, CRGB::DarkOrange, CRGB::Orange, CRGB::Gold, CRGB::Yellow};

unsigned char translation[16][16] = {
        {0,31,32,63,64,95,96,127,128,159,160,191,192,223,224,255},
        {1,30,33,62,65,94,97,126,129,158,161,190,193,222,225,254},
        {2,29,34,61,66,93,98,125,130,157,162,189,194,221,226,253},
        {3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252},
        {4,27,36,59,68,91,100,123,132,155,164,187,196,219,228,251},
        {5,26,37,58,69,90,101,122,133,154,165,186,197,218,229,250},
        {6,25,38,57,70,89,102,121,134,153,166,185,198,217,230,249},
        {7,24,39,56,71,88,103,120,135,152,167,184,199,216,231,248},
        {8,23,40,55,72,87,104,119,136,151,168,183,200,215,232,247},
        {9,22,41,54,73,86,105,118,137,150,169,182,201,214,233,246},
        {10,21,42,53,74,85,106,117,138,149,170,181,202,213,234,245},
        {11,20,43,52,75,84,107,116,139,148,171,180,203,212,235,244},
        {12,19,44,51,76,83,108,115,140,147,172,179,204,211,236,243},
        {13,18,45,50,77,82,109,114,141,146,173,178,205,210,237,242},
        {14,17,46,49,78,81,110,113,142,145,174,177,206,209,238,241},
        {15,16,47,48,79,80,111,112,143,144,175,176,207,208,239,240}
    };

short fire_energy[16][16];

void setup() {
    delay(1000);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, 256).setCorrection(TypicalSMD5050);
    FastLED.setBrightness(16);
    memset(fire_energy, 0, sizeof(fire_energy));
}

void fireAnimation() {
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

void hueAnimation(int offset) {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]].setHSV(i + offset, 255, 255);
        }
}

void hueSmallAnimation(int offset) {
    for (int i = 0; i < 256; i++) {
        int color = offset + i;
        if (color > 255) {
            color = color - 256;
        }
        leds[i].setHSV(color, 255, 255);
    }
}

void randomBlinks() {
    for (int i = 0; i < 256; i++) {
        leds[i].setHSV(random(256), 255,255);
    }
}

uint32_t matrix_grad[4] = {0x000000, 0x002000, 0x008000, 0x00FF00};

char martix_points[16][16];

void matrixEffect() {
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 15; j++) {
            martix_points[i][j] = martix_points[i][j + 1];
        }

    for (int i = 0; i < 16; i++) {
        if (random(10) == 1) {
            martix_points[i][15] = 3;
        } else {
            if (martix_points[i][14] > 0) {
                martix_points[i][15] = martix_points[i][14] - 1;
            } else {
                martix_points[i][15] = 0;
            }
        }
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            leds[translation[i][j]] = matrix_grad[martix_points[i][j]];
        }
    }
}

void loop() {
    int offset = 239;
    while (true) {
        fireAnimation();
        //hueAnimation(offset);
        //hueSmallAnimation(offset);
        //randomBlinks();
        //matrixEffect();
        FastLED.show();
        delay(100);
        offset--;
        if (offset < 0) offset = 239;
    }
    // while (true) {
    //     for (int i = 0; i < 64; i++) {
    //         leds[random(256)] = colors[random(5)];
    //     }
    //     FastLED.show();
    //     delay(100);
    // }
}
