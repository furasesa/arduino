#include <Arduino.h>
#include <WS2818.h>

Sled::Sled (uint8_t pin) : Adafruit_NeoPixel (NUMPIXELS, pin, PIXEL_FORMAT) {
    _pin = pin;
}

