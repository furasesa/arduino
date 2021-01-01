#include "screen_manager.h"
#include "fonts.h"

#define NUMBER_OF_COLUMN    8
#define NUMBER_OF_ROW       4

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
  selector->setBoundaries(0, 1000, true);
  setFont(FONT_610);
  begin();
}

u8g2_uint_t SSD1306::designWidth(){
  return getDisplayWidth()-8; // 15*8 = 120
}
u8g2_uint_t SSD1306::designHeight(){
  return getDisplayHeight()-4; // 15*4 = 60
}
/*
  @brief   Set Title
  @param   String Title
*/
void SSD1306::setTitle(String content){
    // setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    int content_length = content.length() + 3;
    content.toCharArray(charContent, content_length);
    u8g2_uint_t x = designWidth() / NUMBER_OF_COLUMN;
    u8g2_uint_t y = designHeight()/NUMBER_OF_ROW;
    drawStr(x, y, charContent);
    drawHLine(0,15, 128);
}

/*
  @brief   Set Contents
  @param   uint8_t x column
  @param   uint8_t y= 15+(row*15);
  @param   String content
*/
void SSD1306::setContent( uint8_t column, uint8_t row, String content){
    // setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    int content_length = content.length() + 3;
    content.toCharArray(charContent, content_length);

    u8g2_uint_t x = (column+1)*designWidth() / NUMBER_OF_COLUMN;
    u8g2_uint_t y = (row+1)*designHeight()/NUMBER_OF_ROW;
    drawStr(x, y, charContent);
}

/*
@brief  draw rectangle as selector
@param  uint8_t row. start with row num 2. 1 is title
@param  uint8_t act_num. return number when button clicked
@param  bool    button_listener. listening button, returning act_num
*/
uint8_t current_row = 1;
uint8_t SSD1306::rectPointer(uint8_t limit_row){

  if (selector->encoderDelta < 0) pointer_row--;
  if (selector->encoderDelta > 0) pointer_row++;
  if (pointer_row >= limit_row){
    pointer_row = limit_row;
  } else if (pointer_row <= 1){
    pointer_row = 1;
  }
  delay (10);

  u8g2_uint_t x = 5;
  u8g2_uint_t w = 100;
  u8g2_uint_t h = designHeight()/NUMBER_OF_ROW; //15

  #ifdef DEBUG
  if (current_row != pointer_row){
    current_row = pointer_row;
    Serial.print("pointer_row:" );
    Serial.println(pointer_row);
  }
  #endif

  u8g2_uint_t y = (pointer_row)*h+(0.25*h); // (1-1)*15+7.5
  u8g2_uint_t r = 3;
  drawRFrame(x,y,w,h,r);
  if (selector->buttonPressed) {
    return pointer_row;
  } else return 0;
}

void SSD1306::setHome(){
  selector->listenEncoderChanges();
  setTitle("STATUS");

  setContent(1,1, "Set Timer");
  setContent(1,2, "Set Auto");
  setContent(1,3, "run");
  // drawFrame(0,0,getDisplayWidth(),getDisplayHeight() );

  uint8_t button_clicked = rectPointer(3);
  
  if (button_clicked > 0){
    #ifdef DEBUG
    Serial.print("Home: ");
    Serial.println(button_clicked);
    #endif
    if (button_clicked == 1) selected_menu = 1;
    // if (return_number == 2) setAuto();
    if (button_clicked == 3) selected_menu = 255;
  }
}

void SSD1306::setTimer(){
  selector->listenEncoderChanges();
  setTitle("SET TIMER"); 

  setContent(1,1, "Kembali <-"); //1-4
  setContent(1,2, "Detik: "); //5-8
  setContent(1,3, "Menit: "); //9-12

  setContent(4,2, String(second));
  setContent(4,3, String(minute));

  uint8_t button_clicked = rectPointer(3);

  if (button_clicked > 0){
    #ifdef DEBUG
    Serial.print("Timer: ");
    Serial.println(button_clicked);
    #endif
    if (button_clicked == 1) selected_menu = 0;
    if (button_clicked == 2) selected_menu = 3;
    if (button_clicked == 3) selected_menu = 4;
  }
}

// void setAuto(){}

void SSD1306::setSecond(){
  selector->listenEncoderChanges();

  setTitle("SET SECOND"); 

  if (selector->encoderDelta > 0) second++;
  if (selector->encoderDelta < 0) second--;

  if (second > 59) second = 59;
  if (second < 0 ) second = 0;

  setContent(1,1, String(second));
  if (selector->buttonPressed) selected_menu = 1;
}

void SSD1306::setMinute(){
  selector->listenEncoderChanges();

  setTitle("SET MINUTE"); 

  if (selector->encoderDelta > 0) minute++;
  if (selector->encoderDelta < 0) minute--;

  if (minute > 59) minute = 59;
  if (minute < 0 ) minute = 0;

  setContent(1,2, String(minute));
  if (selector->buttonPressed) selected_menu = 1;
}


void SSD1306::run(){
  selector->listenEncoderChanges();

  time = second * minute;

  setTitle("RUN TIMER"); 
  setContent(1,1, String(minute));
  setContent(3,1, ":");
  setContent(4,1, String(second));

  Serial.print(minute);
  Serial.print(" : ");
  Serial.print(second);

  delay(1000);
  second--;
  if (second == 0 && minute > 0){
    second = 60;
    minute--;
  }
}


void SSD1306::start(){
  #ifdef DEBUG
  selector->debugAll();
  #endif
  clearBuffer();

  if (selected_menu == 0) setHome();
  if (selected_menu == 1) setTimer();
  // // if (selected == 2) setAuto();
  if (selected_menu == 3) setSecond();
  if (selected_menu == 4) setMinute();
  if (selected_menu == 255) run();
  sendBuffer();
}
