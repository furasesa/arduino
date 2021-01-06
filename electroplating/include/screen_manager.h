#include "U8g2lib.h"
#include "SPI.h"
#include "Wire.h"
#include "pins.h"
#include "selector.h"

// U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /*
// data=*/ 12, /* cs=*/ 25, /* dc=*/ 26, /* reset=*/ 27);


class SSD1306 : public U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI {
    public:
    SSD1306 (
        const u8g2_cb_t *rotation = U8G2_R0,
        uint8_t clock   = CLK,
        uint8_t data    = DATA,
        uint8_t cs      = CS,
        uint8_t dc      = DC,
        uint8_t reset   = RST
    );
    void setup();
    void start();
    
    private:
    u8g2_uint_t designWidth();
    u8g2_uint_t designHeight();
    
    uint8_t rectPointer(uint8_t limit_row);

    void setTitle(String Title);
    void setContent(uint8_t column, uint8_t row, String content);

    uint8_t selected_menu    = 0;
    /*
    0 = setHome
    1 = setTimer
    2 = setAuto
    3 = setSecond
    4 = setMinute
    255 = run
    */

    void setHome();
    void setTimer();
    void setSecond();
    void setMinute();

    void run();

    uint8_t hour    = 0;
    uint8_t minute  = 0;
    uint8_t second  = 0;
    uint16_t time;

    uint8_t pointer_row = 1;

    char charContent[];
  
};