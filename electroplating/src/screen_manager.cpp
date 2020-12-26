#include "screen_manager.h"

Selector *selector;
/*
  @brief    Work for 1.3" v.2.0 LCD with SPI wire
  @param    rotation: LCD rotation
  @param    clock: CLK pin
  @param    data: MOSI pin
  @param    cs: CS pin
  @param    dc: DC pin
  @param    rst: RST pin
*/
SSD1306::SSD1306 (
    const u8g2_cb_t *rotation,  uint8_t clock,
    uint8_t data,               uint8_t cs,
    uint8_t dc,                 uint8_t rst
    ) : U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI (rotation, clock, data, cs, dc, rst){}

/*
  @brief    Init LCD & Rotarty encoder
*/
void SSD1306::setup(){
  selector = new Selector();
  selector->begin();
  selector->setup([]{selector->readEncoder_ISR();});
  selector->setBoundaries(0, 1000, false);
  setFont(u8g2_font_mercutio_basic_nbp_tf);
  begin();
}

/*
  @brief   Set Contents
  @param   uint8_t row. y= row*15
  @param   String content
*/
void SSD1306::setContent( uint8_t column, uint8_t row, String content){
    // setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    int content_length = content.length() + 3;
    content.toCharArray(charContent, content_length);
    u8g2_uint_t x = 10+(column-1)*getDisplayWidth()/2;
    u8g2_uint_t y = 15+(row*15);
    drawStr(x, y, charContent);
}

// String  strContent10     = "";
// char    charContent10[]  = "";
// String  strContent11     = "";
// char    charContent11[]  = "";


// void SSD1306::draw(const char*t, const char *s){
//   firstPage();
//   do {
//     drawStr(10,10,t);
//     drawHLine(0,15, 128);
//     drawStr(0,30,s);    
//     drawFrame(0,0,getDisplayWidth(),getDisplayHeight() );
//   } while ( nextPage() );
//   delay(500);
// }

void SSD1306::start(){
    clearBuffer();

    selector->listenEncoderChanges();

    drawStr(10,10,"HOME");
    drawHLine(0,15, 128);
    // Content
    if (selector->toggleState) {
      // button pressed
      setContent(1,1, "Counter");
      setContent(2,1, String(selector->counter));
      // strContent10 = "Counter: ";
      // strContent11 = String(selector->encoderValue);
    } else {
      setContent(1,1, "Encoder");
      setContent(2,1, String(selector->encoderValue));
      // strContent10 = "Encoder: ";
      // strContent11 = String(selector->encoderValue);
    }
    // strContent10.toCharArray(charContent10, 10);
    // strContent11.toCharArray(charContent11, 4);
    // draw("STATUS", charContent1);
    // drawStr(10, 30, charContent10);
    // drawStr(75, 30, charContent11);

    #ifdef DEBUG
    selector->debugAll();
    #endif
    drawFrame(0,0,getDisplayWidth(),getDisplayHeight() );
    sendBuffer();
    // delay(100);
}