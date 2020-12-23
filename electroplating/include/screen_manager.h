#include "U8g2lib.h"
#include "SPI.h"
#include "Wire.h"

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /*
data=*/ 12, /* cs=*/ 25, /* dc=*/ 26, /* reset=*/ 27);

uint8_t lcd_w = 128;
uint8_t lcd_h = 64;
uint8_t margin = 10; //margin

uint8_t max_title_length = lcd_w-(4*margin);
uint8_t max_content_length = lcd_w-(2*margin);
char title_char[] = "Title";
char content_char[] = "content";


void setTitle(String title){
    u8g2.setFont(u8g2_font_t0_16b_tn); //12px
    title.toCharArray(title_char, max_title_length);
    u8g2.drawStr(margin, margin, title_char);
}

void setContent(uint8_t row, String content){
    u8g2.setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    content.toCharArray(content_char, max_content_length);
    u8g2_uint_t y = row*30;
    u8g2.drawStr(margin, y, title_char);
}

void home(){
    u8g2.clearBuffer();
    // home content: V/A sensor
    setTitle("HOME");
    setContent(1, "option1");
    setContent(2, "option2");
}


void setTimer(){
    // set timer based
}

void run(){
    // run
}