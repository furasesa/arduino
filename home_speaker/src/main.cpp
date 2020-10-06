#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <color_palette.h>

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    tft.reset();
    uint16_t identifier = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(identifier, HEX);
    if (identifier == 0xEFEF) identifier = 0x9486;
    tft.begin(identifier);
    //  tft.fillScreen(BLACK);
}

char *msg[] = { "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV" };

uint8_t aspect;
uint16_t color_list [] = {Black, Red, Pink, Purple, DeepPurple, Indigo, Blue, 
                          LightBlue, Cyan, Teal, Green, LightGreen, Lime,
                          Yellow, Amber, Orange, DeepOrange, Brown, Grey, BlueGrey};
int color_number = 0;

void loop()
{
    // put your main code here, to run repeatedly:
    uint16_t x = 50, y = 100;
    tft.setRotation(aspect);
    tft.fillScreen(color_list[color_number]);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.println(msg[aspect]);
    tft.setCursor(x, y);
    tft.println("[x=" + String(x) + ",y=" + String(y) + "]");
    delay(5000);
    tft.println("INVERT ON");
    tft.invertDisplay(true);
    delay(1000);
    tft.invertDisplay(false);
    tft.println("INVERT OFF");
    delay(1000);
    if (++aspect >= 4) aspect = 0;
    if (++color_number >= 20) color_number = 0;
}