#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#ifdef __USE_LCD__
    #include <Wire.h>
    #include <Adafruit_GFX.h> 
    #include <MCUFRIEND_kbv.h>
    //  Only for MEGA
    //	MCUFRIEND_kbv(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4); A0-A4 is used
    //  digital pwm used for lcd(D2-D7=2-7, D0=8, d1=9), used for SD (SS=10, DI=11, DO=12, SCK=13)
    //  MSGEQ7
    #define STROBE      22
    #define RESET       23
    //  WS2812
    #define LEDC1       24
    #define LEDC2       25
    #define LEDC3       26
    #define LEDC4       27
    #define LEDC5       28
    //  Analog
    #define MSGEQ7_DATA 59 // A5
#else
    //  MSGEQ7
    #define STROBE      2
    #define RESET       3
    //  WS2812
    #define LEDC1       4
    #define LEDC2       5
    #define LEDC3       6
    #define LEDC4       7
    #define LEDC5       8
    #ifdef ARDUINO_AVR_UNO
        #define MSGEQ7_DATA 14 // A0
    #elif ARDUINO_AVR_MEGA2560
        #define MSGEQ7_DATA 54 // A0
    #endif
    #define DUMMY_TFT TFT
#endif

#include <math.h>
#include <color_palette.h>
#include <definition.h>

COLOR COLOR_MONITOR;

Adafruit_NeoPixel led_band_1(NUMPIXELS, LEDC1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led_band_2(NUMPIXELS, LEDC2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led_band_3(NUMPIXELS, LEDC3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led_band_4(NUMPIXELS, LEDC4, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel led_band_5(NUMPIXELS, LEDC5, NEO_RGB + NEO_KHZ800);

Adafruit_NeoPixel Led_Array[BAND] = {led_band_1, led_band_2, led_band_3, led_band_4, led_band_5};

void color_monitor(uint8_t color_value){
    COLOR_MONITOR.value = color_value;
    Serial.println("");
    Serial.print("   Red: ");
    Serial.print(COLOR_MONITOR.rgb.R);
    Serial.print("   Green: ");
    Serial.print(COLOR_MONITOR.rgb.G);
    Serial.print("   Blue: ");
    Serial.println(COLOR_MONITOR.rgb.B);
}

void led_manager (int column, int current_level){
    int led_level = (current_level < 5) ? current_level : current_level % 5;
    if (current_level == 5){
        for (int i=0; i < 5; i++){
            int led_pos = current_level-i;
            color.value = Blue + 1024 * 5;
            Led_Array[column].setPixelColor(led_pos-i, color.rgb.R, color.rgb.G, color.rgb.B);
            color_monitor(color.value);
        }
    }
    else{
        for (int i=0; i < 5; i++){
            int led_pos = led_level - i;
            if (led_pos == 0 && current_level > 5){
                led_pos = 5;
                // led num 5
            }
            else if (led_pos >= 1){
                color.value = Blue + (1024 * (current_level-i));
                // value = Blue + (1024 * 10), 9, 8, 7, 6
                Led_Array[column].setPixelColor(led_pos, color.rgb.R, color.rgb.G, color.rgb.B);
                color_monitor(color.value);
            }
        }
    }
}
