

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <math.h>

// WS2812
#define PIN         4
#define NUMPIXELS   25
#define DELAYVAL    500 // Time (in milliseconds) to pause between pixels
#define BRIGHTNESS  15
// MSGEQ7
#define STROBE      2
#define RESET       3
#define MSGEQ7_DATA 14 // A0
#define BAND        5 // Spectrum Total

// No Use
// int strobePin = 2;
// int resetPin = 3;
// int MSGEQ7_DATAIn = A0;

// band 1 100       Hz
// band 2 310~330   Hz
// band 3 915~950   Hz
// band 4 2875~3090 Hz
// band 5 8145~11225Hz

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int spectrumBand[BAND]; // MSGEQ7 Palsu 5 band

void setup(){
  Serial.begin(9600);
  pixels.begin();

  // Define pin mode
  pinMode       (STROBE, OUTPUT);
  pinMode       (RESET, OUTPUT);
  pinMode       (MSGEQ7_DATA, INPUT);

  // init
  digitalWrite  (RESET, HIGH);
  delay(1);
  digitalWrite  (RESET, LOW);
  digitalWrite  (STROBE, HIGH);
  delay(1);
  
}

void led_mgmt(int value, int led_start){
  // min value is like 30 max is 1023
  // from spectum color, lowest is blue, green, and highest is Red
  // so 1024/3 = 341 ~ 340
  // 5 leds for each band, so each led is +68 and 255 color set.
  

  // for blue color
  if (value>0 && value<=340) {
    if (value<=68){
      // level 1, 68 is blue 255
      int color = round(float(value)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 0, color));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>68 && value<=136){
      int color = round((float(value)-68)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, color));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>136 && value<=204){
      int color = round((float(value)-136)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, color));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>204 && value<=272){
      int color = round((float(value)-204)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, color));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>272 && value<=340){
      int color = round((float(value)-272)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 255));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, color));
    }
    
  }

  // Grenn Color
  else if (value>340 && value<=680) {
    int start_value = 340;
    int led1 = start_value+68;
    int led2 = start_value+(68*2);
    int led3 = start_value+(68*3);
    int led4 = start_value+(68*4);
    int led5 = start_value+(68*5);
    
    if (value>340 && value <= led1){
      int color = round((float(value)-start_value)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(color, 0, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led1 && value<=led2){
      int color = round((float(value)-led2)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(color, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led2 && value<=led3){
      int color = round((float(value)-led3)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(color, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led3 && value<=led4){
      int color = round((float(value)-led4)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(color, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led4 && value<=led5){
      int color = round((float(value)-led5)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(255, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(color, 0, 0));
    }
  }
  
  else if (value>680 && value<=1024) {
    int start_value = 680;
    int led1 = start_value+68;
    int led2 = start_value+(68*2);
    int led3 = start_value+(68*3);
    int led4 = start_value+(68*4);
    int led5 = start_value+(68*5);
    
    if (value>340 && value <= led1){
      int color = round((float(value)-start_value)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led1 && value<=led2){
      int color = round((float(value)-led2)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, color, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led2 && value<=led3){
      int color = round((float(value)-led3)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, color, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 0, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led3 && value<=led4){
      int color = round((float(value)-led4)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, color, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, 0, 0));
    }
    else if (value>led4 && value<=led5){
      int color = round((float(value)-led5)*3.75);
      pixels.setPixelColor(led_start, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+2, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+3, pixels.Color(0, 255, 0));
      pixels.setPixelColor(led_start+4, pixels.Color(0, color, 0));
    }
  }
}

void loop() {
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  
  for (int i = 0; i < BAND; i++){
    digitalWrite      (STROBE, LOW);
    delayMicroseconds (100);
    spectrumBand[i] = analogRead(MSGEQ7_DATA);
    digitalWrite      (STROBE, HIGH);
    delayMicroseconds (1);
  }
  // Band 1 : Led number 0-4
  led_mgmt(spectrumBand[0], 0);
  led_mgmt(spectrumBand[1], 5);
  led_mgmt(spectrumBand[2], 10);
  led_mgmt(spectrumBand[3], 15);
  led_mgmt(spectrumBand[4], 20);

  pixels.show();
  delayMicroseconds(100);
  
  //for (int i = 0; i < BAND; i++) {
  //  Serial.print      (spectrumBand[i]);
  //  Serial.print      ("  ");
  //}
  //Serial.println();
}
