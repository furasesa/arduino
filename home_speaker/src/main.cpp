#include <main.h>


// spectrum_display = new Adafruit_NeoPixel(NUMPIXELS, LED_WIRE, PIXEL_FORMAT)

MSGEQ7 *msgeq7;
WS2818 *led_disp;

void setup(){
  Serial.begin(9600);
  msgeq7 = new MSGEQ7();
  led_disp = new WS2818();

  msgeq7->begin();
  led_disp->begin();
  led_disp->ref_data_range(50, 1024);
  led_disp->ref_color_range(BLUE, RED, COLOR_DIFF_LEVEL);
  
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

  msgeq7 -> monitor_t();
  
}

uint16_t data[5];
void loop(){
  led_disp->clear();
  led_disp->setBrightness(BRIGHTNESS);

  msgeq7->read();
  data[0] = msgeq7->getData(0);

  // led_disp->run();
  // led_disp->run()


  // double bandd = double(spectrumBand[i]) / double(1024.00);
  // Serial.print("bandd: ");
  // Serial.println(bandd);

  // int current_level_band_1 = roundf(double(spectrumBand[0]) / 1024.00 * LENGTH_LEVEL)-1;
  // int led_pos_1 = (current_level_band_1 < 5) ? current_level_band_1 : current_level_band_1 % 5;
  // Serial.print("led level:");
  // Serial.print(led_pos_1);
  // Serial.print("->");
  // Serial.println(current_level_band_1);
  
  // if (current_level_band_1 < 5){
  //   for (int i = 0; i < 5; i++){
  //     uint32_t new_color = (current_level_band_1 >= i+1) ? BLUE + 460221 * (i+1) : Black;
  //     uint8_t   r = getRed(new_color);
  //     uint8_t   g = getGreen(new_color);
  //     uint8_t   b = getBlue(new_color);
  //     led_band_1.setPixelColor(i, r, g, b);
  //     Serial.print("led");
  //     Serial.print(i+1);
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println(", ");


  //   }
  // }
  // else {
  //   for (int i = 0; i < 5; i++) {
  //     if (led_pos_1 < 0){
  //       led_pos_1 = 4;
  //     }
  //     // color.value = BLUE + 460221 * (current_level_band_1-i);
  //     uint32_t new_color = BLUE + 460221 * current_level_band_1;
  //     uint8_t   r = getRed(new_color);
  //     uint8_t   g = getGreen(new_color);
  //     uint8_t   b = getBlue(new_color);
  //     led_band_1.setPixelColor(led_pos_1, r, g, b);
  //     Serial.print("led");
  //     Serial.print(i+1);
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println(", ");
  //     led_pos_1--;
  //   }
  // }

  // for (int band = 0; band < BAND; band++){
  //   int current_level_band = roundf(double(spectrumBand[band]) / 1024.00 * LENGTH_LEVEL)-1;
  //   int led_pos = (current_level_band < 5) ? current_level_band : current_level_band % 5;
    
  //   if (current_level_band < 5){
  //     for (int i = 0; i < 5; i++){
  //       uint32_t new_color = (current_level_band >= i+1) ? BLUE + 460221 * (i+1) : Black;
  //       uint8_t   r = getRed(new_color);
  //       uint8_t   g = getGreen(new_color);
  //       uint8_t   b = getBlue(new_color);
  //       if (band == 0 ){
  //         led_band_1.setPixelColor(i, r, g, b);

  //       }
  //       else if (band == 1){
  //         led_band_2.setPixelColor(i, r, g, b);
  //       }
  //       else if (band == 2){
  //         led_band_3.setPixelColor(i, r, g, b);
  //       }
  //       else if (band == 3){
  //         led_band_4.setPixelColor(i, r, g, b);
  //       }
  //       else if (band == 4){
  //         led_band_5.setPixelColor(i, r, g, b);
  //       }
  //     }
  //   }
  //   else {
  //     for (int i = 0; i < 5; i++) {
  //       if (led_pos < 0){
  //         led_pos = 4;
  //       }
  //       // color.value = BLUE + 460221 * (current_level_band_1-i);
  //       uint32_t new_color = BLUE + 460221 * current_level_band;
  //       uint8_t   r = getRed(new_color);
  //       uint8_t   g = getGreen(new_color);
  //       uint8_t   b = getBlue(new_color);
        
  //       if (band == 0 ){
  //         led_band_1.setPixelColor(led_pos, r, g, b);

  //       }
  //       else if (band == 1){
  //         led_band_2.setPixelColor(led_pos, r, g, b);
  //       }
  //       else if (band == 2){
  //         led_band_3.setPixelColor(led_pos, r, g, b);
  //       }
  //       else if (band == 3){
  //         led_band_4.setPixelColor(led_pos, r, g, b);
  //       }
  //       else if (band == 4){
  //         led_band_5.setPixelColor(led_pos, r, g, b);
  //       }
  //       led_pos--;
  //     }
  //   }
    
  // }

  // // Serial.println("");
  // led_band_1.show();
  // led_band_2.show();
  // led_band_3.show();
  // led_band_4.show();
  // led_band_5.show();
  // delay(10);
  
}