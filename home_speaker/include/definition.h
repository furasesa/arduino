//  Used by LCD
//	MCUFRIEND_kbv(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4); //shield wiring
//  digital pwm 2-8


//  MSGEQ7
#define STROBE      11 //22
#define RESET       12 //23
//  WS2812
#define WS2812      10 // 24
//  Analog
#define MSGEQ7_DATA 59 // A5
#define BAND        5 // Spectrum Total

#define NUMPIXELS   25
#define DELAYVAL    500 // Time (in milliseconds) to pause between pixels
#define BRIGHTNESS  10

#define LED_EACH_COLUMN     5
#define MAX_SPECTRUM_VALUE  1024
#define SPECTRUM_LEVEL      6 // Total Led in column
