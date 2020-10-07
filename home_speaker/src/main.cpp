#include <main.h>

int spectrumBand[BAND];

void setup(){
  Serial.begin(9600);
  #ifdef __USE_LCD__
    MCUFRIEND_kbv tft;
    tft.reset();
    uint16_t identifier = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(identifier, HEX);
    if (identifier == 0xEFEF) identifier = 0x9486;
    tft.begin(identifier);
    tft.fillScreen(DBlueGrey);
    tft.setCursor(10,10);
    tft.setTextSize(3);  
  #endif
  led_band_1.begin();
  led_band_2.begin();
  led_band_3.begin();
  led_band_4.begin();
  led_band_5.begin();
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

void loop(){
  led_band_1.clear();
  led_band_2.clear();
  led_band_3.clear();
  led_band_4.clear();
  led_band_5.clear();
  led_band_1.setBrightness(BRIGHTNESS);
  led_band_2.setBrightness(BRIGHTNESS);
  led_band_3.setBrightness(BRIGHTNESS);
  led_band_4.setBrightness(BRIGHTNESS);
  led_band_5.setBrightness(BRIGHTNESS);

  for (int i = 0; i < BAND; i++){
    digitalWrite      (STROBE, LOW);
    delayMicroseconds (100);
    spectrumBand[i] = analogRead(MSGEQ7_DATA);
    digitalWrite      (STROBE, HIGH);
    delayMicroseconds (1);
  }

  for (int i = 0; i < BAND; i++) {
    int current_level = roundf(spectrumBand[i]/1024*LENGTH_LEVEL);
    led_manager(i, current_level);
  }
  led_band_1.show();
  led_band_2.show();
  led_band_3.show();
  led_band_4.show();
  led_band_5.show();
  
}