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
  // selector->setBoundaries(0, 1000, false);
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
  @brief   Set Contents
  @param   uint8_t x column
  @param   uint8_t y= 15+(row*15);
  @param   String content
*/
void SSD1306::setContent( uint8_t column, uint8_t row, String content){
    // setFont(u8g2_font_mercutio_basic_nbp_tf); //10pxh
    int content_length = content.length() + 3;
    content.toCharArray(charContent, content_length);
    u8g2_uint_t x = column*designWidth() / NUMBER_OF_COLUMN;
    u8g2_uint_t y = row*designHeight()/NUMBER_OF_ROW;
    drawStr(x, y, charContent);
}

void SSD1306::rectPointer(uint8_t row){
  u8g2_uint_t x = 5;
  u8g2_uint_t w = 100;
  u8g2_uint_t h = designHeight()/NUMBER_OF_ROW; //15
  u8g2_uint_t y = (row-1)*h+(0.25*h); // (1-1)*15+7.5
  u8g2_uint_t r = 3;
  drawRFrame(x,y,w,h,r);
}

// bool selected_target = false;

uint8_t second=0;
uint8_t minute=0;
uint8_t hour  =0;

// void SSD1306::TimerDisplay(){
  
//   selector->setBoundaries(0, 9, true);
//   // clearBuffer();

//   setContent(1,1, "SET TIMER"); 
//   drawHLine(0,15, 128);
//   if(selector->encoderValue <= 5){
//     setContent(1,2, "Kembali <-"); //0-1
//     setContent(1,3, "Detik: "); //2-3
//     setContent(1,4, "Menit: "); //4-5
//   } else if (selector->encoderValue > 5){
//     // ----------page 2 --------------
//     setContent(1,2, "Jam:"); // 6-7
//     setContent(1,3, "simpan"); // 8-9
//     setContent(1,4, "");
//   }

//   if (selector->encoderValue <= 1) HomeDisplay();
//   if (selector->encoderValue >= 2 && selector->encoderValue <= 3) {
//     //set detik
//     if (selector->toggleState){
//       selector->setBoundaries(0, 59, true);
//       second = selector->encoderValue;
//     }
//   }

//   // minutes
//   if (selector->encoderValue >= 4 && selector->encoderValue <= 5) {
//     //set detik
//     if (selector->toggleState){
//       selector->setBoundaries(0, 59, true);
//       minute = selector->encoderValue;
//     }
//   }

//   //hour
//   if (selector->encoderValue >= 6 && selector->encoderValue <= 7) {
//     //set detik
//     if (selector->toggleState){
//       selector->setBoundaries(0, 23, true);
//       hour = selector->encoderValue;
//     }
//   }
//   setContent(3,3, String(second)); //2-3
//   setContent(3,4, String(minute)); //4-5
//   setContent(3,2, String(hour)); // 6-7


//   // sendBuffer();
// }

void SSD1306::start(){
  #ifdef DEBUG
  selector->debugAll();
  #endif
  selector->setBoundaries(1, 8, true);
  clearBuffer();

  selector->listenEncoderChanges();

  setContent(1,1, "STATUS");
  drawHLine(0,15, 128);
  setContent(1,2, "Set Timer");
  setContent(1,3, "Set Auto");
  setContent(1,4, "run");
  // drawFrame(0,0,getDisplayWidth(),getDisplayHeight() );

  if (selector->encoderValue <= 4) {
    rectPointer(2);
  }
  if (selector->encoderValue >= 5) {
    rectPointer(3);
  }
  if (selector->encoderValue <5 && selector->buttonPressed){
    is_Timer = true; is_Auto = false;
    selector->reset();
  }
  if (selector->encoderValue >5 && selector->buttonPressed) {
    is_Auto = true; is_Timer = false;
    selector->reset();
  }

  while (is_Timer){
    #ifdef DEBUG
    selector->debugAll();
    #endif
    clearBuffer();
    selector->listenEncoderChanges();
    
    selector->setBoundaries(1, 20, true);

    setContent(1,1, "SET TIMER"); 
    drawHLine(0,15, 128);
    if(selector->encoderValue <= 12){
      setContent(1,2, "Kembali <-"); //1-4
      setContent(1,3, "Detik: "); //5-8
      setContent(1,4, "Menit: "); //9-12

      setContent(4,3, String(second));
      setContent(4,4, String(minute));
      if (selector->encoderValue >= 1 && selector->encoderValue <= 4) {
        rectPointer(2);
        if (selector->buttonPressed) break;
      }
      if (selector->encoderValue >= 5 && selector->encoderValue <= 8) {
        rectPointer(3);
        selector->toggleState=0;
        while (selector->toggleState){
          second = selector->encoderValue;
        }
      }
      if (selector->encoderValue >= 9 && selector->encoderValue <= 12) {
        rectPointer(4);
        selector->toggleState=0;
        while (selector->toggleState){
          selector->setBoundaries(0, 59, true);
          minute = selector->encoderValue;
        }
      }

    } else if (selector->encoderValue >= 13){
      // ----------page 2 --------------
      setContent(1,2, "Jam:"); // 13-16
      setContent(4,2, String(hour));
      if (selector->encoderValue >= 13 && selector->encoderValue <= 16) {
        rectPointer(2);
        selector->toggleState=0;
        while (selector->toggleState){
          selector->setBoundaries(0, 23, true);
          hour = selector->encoderValue;
        }
      }
      setContent(1,3, "simpan"); // 17-20
      if (selector->encoderValue >= 17 && selector->encoderValue <= 20) {
        rectPointer(3);
        if (selector->buttonPressed) break;
      }

      setContent(1,4, "");
      
      
    }
    sendBuffer();
  }



  sendBuffer();
}
