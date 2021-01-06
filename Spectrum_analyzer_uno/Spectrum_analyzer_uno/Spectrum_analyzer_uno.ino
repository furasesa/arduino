

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// WS2812
#define PIN         4
#define NUMPIXELS   12
#define DELAYVAL    500 // Time (in milliseconds) to pause between pixels
#define BRIGHTNESS  10
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

int value_to_led(int value){
  // min value is like 30 max is 1023
  // from spectum color, lowest is blue, green, and highest is Red
  // so 1024/3 = 341
  if (value>0 && value<341) {
    // perform as blue
  }
  if (value>=341 && value<682) {
    // perform as green
  }
  if (value>=682 && value<1023) {
    // perform as red
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
  
  for (int i = 0; i < BAND; i++) {
    Serial.print      (spectrumBand[i]);
    Serial.print      ("  ");
  }
  Serial.println();
}
