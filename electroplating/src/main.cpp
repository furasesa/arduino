#include "Arduino.h"
// #include "WiFi.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /*
data=*/ 12, /* cs=*/ 25, /* dc=*/ 26, /* reset=*/ 27);
// IPAddress ip;
char ip_char[] = "xxx.xxx.xxx.xxx";
IPAddress ip;

void setup()
{
  // initialize LED digital pin as an output.
  Serial.begin(115200);
  // Wifi connection
  wifiMulti.addAP("pcp", "AnggaMiMi");
  wifiMulti.addAP("pcpdef", "AnggaMiMi");
  wifiMulti.addAP("npsk");
  u8g2.begin();
}

void loop()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_mercutio_basic_nbp_tf);
  if (wifiMulti.run() == WL_CONNECTED){
    ip = WiFi.localIP();
    ip.toString().toCharArray(ip_char, 16);
    Serial.print("ipaddr: ");
    Serial.println(ip);
  }
  u8g2.drawStr(0,16, ip_char);
  u8g2.sendBuffer();
  delay(500);
}