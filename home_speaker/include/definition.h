/*
Global Definition. public setting
*/

#ifdef __AVR__
    #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#ifdef USE_LCD
    #include <Wire.h>
    #include <Adafruit_GFX.h> 
    #include <MCUFRIEND_kbv.h>
    //  Only for MEGA
    //	MCUFRIEND_kbv(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4); A0-A4 is used
    //  digital pwm used for lcd(D2-D7=2-7, D0=8, d1=9), used for SD (SS=10, DI=11, DO=12, SCK=13)
    //  MSGEQ7
    #define STROBE      22
    #define RESET       23
    #define LD1         24
    //  Analog
    #define ANALOG_PIN 59 // A5
#else
    //  MSGEQ7
    #define STROBE      2
    #define RESET       3
    #define LD1         4
    #ifdef ARDUINO_AVR_UNO
        #define ANALOG_PIN 14 // A0
    #elif ARDUINO_AVR_MEGA2560
        #define ANALOG_PIN 54 // A0
    #endif
#endif

//MSGEQ7
#define BAND                5       // MSGEQ7 band spectrum
#define MIN_SPECTRUM_VALUE  30
#define MAX_SPECTRUM_VALUE  1024
#define COLOR_DIFF_LEVEL    6       // 6 color step for range 0 - 1024


// WS2818
#define BRIGHTNESS          10
#define LED_IN_ROW          5
#define NUM_PIXELS          BAND * LED_IN_ROW
#define DELAY_VALUE         500     // Time (in milliseconds) to pause between pixels