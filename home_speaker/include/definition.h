/*
Spectrum Analyzer
*/
#define BAND                5       // MSGEQ7 band spectrum
#define MAX_SPECTRUM_VALUE  1024
#define COLOR_DIFF_LEVEL    6       // 6 color step for range 0 - 1024

/*
LED WS2818
*/
#define BRIGHTNESS          10
#define NUMPIXELS           5
#define DELAYVAL            500     // Time (in milliseconds) to pause between pixels

//  Calculation
#define LENGTH_LEVEL        COLOR_DIFF_LEVEL*NUMPIXELS

