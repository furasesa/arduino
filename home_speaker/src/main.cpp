#include <main.h>


// spectrum_display = new Adafruit_NeoPixel(NUMPIXELS, LED_WIRE, PIXEL_FORMAT)

MSGEQ7 *msgeq7;
WS2818 *led_disp;

void setup(){
  Serial.begin(115200);

  msgeq7    = new MSGEQ7();
  led_disp  = new WS2818();

  led_disp  -> ref_data_range(50, 1024);
  led_disp  -> ref_color_range(BLUE, RED, COLOR_DIFF_LEVEL);

  msgeq7    -> begin();
  led_disp  -> begin();

  #ifdef USE_LCD
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

  // msgeq7    -> monitor_t();
  // led_disp  -> monitor_t();
  // led_disp  -> pin_check(led_disp->getPin());
}

void loop(){
  led_disp->clear();
  led_disp->setBrightness(BRIGHTNESS);

  // for (int i = 0; i < BAND; i++){
  //   data[i] = msgeq7->read(i);
  // }
  for (int i = 0; i < BAND; i++){
    led_disp -> run(i, msgeq7->read(i));
    led_disp -> show();
  }
  delay(10);
  Serial.println(" ");

  // for (int i = 0; i < BAND; i++){
  //   led_disp -> run(i, data[i]);
  // }
  // led_disp->show();

  delay(10);
}