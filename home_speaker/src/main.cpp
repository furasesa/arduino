#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <math.h>

#include <color_palette.h>
#include <definition.h>

Adafruit_NeoPixel pixels(NUMPIXELS, WS2812, NEO_RGB + NEO_KHZ800);
int spectrumBand[BAND]; // MSGEQ7 Palsu 5 band

//  used for LCD
uint16_t color_list [] = {Black, Red, Pink, Purple, DeepPurple, Indigo, Blue, 
                          LightBlue, Cyan, Teal, Green, LightGreen, Lime,
                          Yellow, Amber, Orange, DeepOrange, Brown, Grey, BlueGrey};

void setup() {
  Serial.begin(9600);
  pixels.begin();

  //  Define pin mode
  pinMode       (STROBE, OUTPUT);
  pinMode       (RESET, OUTPUT);
  pinMode       (MSGEQ7_DATA, INPUT);

  //  reset
  tft.reset();
  digitalWrite  (RESET, HIGH);
  delay(1);
  digitalWrite  (RESET, LOW);
  digitalWrite  (STROBE, HIGH);
  delay(1);

  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);
  tft.fillScreen(DBlueGrey);
  tft.setCursor(10,10);
  tft.setTextSize(3);
}

void led_mgmt(int led_column, int spectrum_value) {

  /* 1024 is the highest level of sepctrum value
  so peak color value is 1024 * SPECTRUM_LEVEL * LED_EACH_COLUMN
  Assuming Blue = 26046, 26046 + (1024 * 6 * 5) = 56766
  */
  // 1024 is level 30
  // int led_matrix[BAND][LED_EACH_COLUMN]; //total band of spectrum & total led in column

  int current_level = roundf(spectrum_value/1024*SPECTRUM_LEVEL*LED_EACH_COLUMN);
  int led_pos = (current_level < 5) ? current_level : current_level % 5;
  int led_num = led_pos * led_column;
  color.value = Blue + (1024 * current_level);
  Serial.print(led_column);
  Serial.print("    ");
  Serial.print(led_pos);
  Serial.print(color.value);
  pixels.setPixelColor(led_num,color.rgb.R, color.rgb.G, color.rgb.B);
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
    led_mgmt(i, spectrumBand[i]); // band number == led column
    
    tft.setTextSize(3);
    tft.print      (spectrumBand[i]);
    tft.print      ("  ");
    tft.println();
  }

  pixels.show();
  delayMicroseconds(100);
}