#include "screen_manager.h"
#include "U8g2lib.h"
#include "SPI.h"
#include "Wire.h"
#include "pins.h"

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
  selector->setBoundaries(-100, 100, true);
  begin();
}

/*
  @brief   Set Contents
  @param   uint8_t row. y= row*15
  @param   String content
*/
void SSD1306::setContent(uint8_t row, String content){
    setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    content.toCharArray(content_char, max_content_length);
    u8g2_uint_t y = row*15;
    drawStr(margin, y, content_char);
}

void SSD1306::start(){
    clearBuffer();
    selector->listenEncoder();
    selector->getSwitchState();
    selector->getMovement();
    selector->getCounter();
    selector->getEncoderValue();
    // rotaryValue = selector->getEncoderValue();
    // switchPrint = selector->getSwitchState();
    setContent(1, "Content 1"); //15
    setContent(2, "Content 2"); //30
    setContent(3, "Content 3"); //45
    setContent(4, "Content 4"); //60 
    sendBuffer();
}