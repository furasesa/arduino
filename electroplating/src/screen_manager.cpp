#include "screen_manager.h"
#include "U8g2lib.h"
#include "SPI.h"
#include "Wire.h"
#include "pins.h"

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
    ) : U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI (rotation, clock, data, cs, dc, rst)
{
    _clock_pin = clock;
    _data_pin = data;
}

/*
  @brief   Set Conten
  @param   uint8_t row. y= row*15
  @param   String content
*/
void SSD1306::setContent(uint8_t row, String content){
    setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    content.toCharArray(content_char, max_content_length);
    u8g2_uint_t y = row*15;
    drawStr(margin, y, title_char);
}

void SSD1306::start(){
    clearBuffer();
    setContent(1, "Content 1");
    setContent(2, "Content 2");
    setContent(3, "Content 3");
    setContent(4, "Content 4");
    sendBuffer();
}