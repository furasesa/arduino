#ifndef WS2818_H
#define WS2818_H

#include <Adafruit_NeoPixel.h>
#include <definition.h>

#ifdef __USE_LCD__
    #ifdef ONE_WIRE_LED
    #define LED_WIRE    24
    #else
    //  WS2812
    #define LED1        24
    #define LED2        25
    #define LED3        26
    #define LED4        27
    #define LED5        28
    #endif
#else
    #ifdef ONE_WIRE_LED
    #define WS2818_PIN  4
    #else
    //  WS2812
    #define LED1        4
    #define LED2        5
    #define LED3        6
    #define LED4        7
    #define LED5        8
    #endif
#endif

#define PIXEL_FORMAT NEO_RGB + NEO_KHZ800

class Sled:public Adafruit_NeoPixel {
    public:
        Sled::Sled  (uint8_t pin=LED_WIRE);
    private:
        uint8_t     _pin;
};


#endif
// Adafruit_NeoPixel led_band_1(NUMPIXELS, LED1, NEO_RGB + NEO_KHZ800);
// Adafruit_NeoPixel led_band_2(NUMPIXELS, LED2, NEO_RGB + NEO_KHZ800);
// Adafruit_NeoPixel led_band_3(NUMPIXELS, LED3, NEO_RGB + NEO_KHZ800);
// Adafruit_NeoPixel led_band_4(NUMPIXELS, LED4, NEO_RGB + NEO_KHZ800);
// Adafruit_NeoPixel led_band_5(NUMPIXELS, LED5, NEO_RGB + NEO_KHZ800);

// Adafruit_NeoPixel led_wire(NUMPIXELS, LED_WIRE, NEO_RGB + NEO_KHZ800);


