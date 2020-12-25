#include "U8g2lib.h"
#include "SPI.h"
#include "Wire.h"
#include "pins.h"

// U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /*
// data=*/ 12, /* cs=*/ 25, /* dc=*/ 26, /* reset=*/ 27);

class SSD1306 : public U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI {
    public:
    SSD1306 (
        const u8g2_cb_t *rotation = U8G2_R0,
        uint8_t clock   = CLOCK,
        uint8_t data    = DATA,
        uint8_t cs      = CS,
        uint8_t dc      = DC,
        uint8_t reset   = RESET
    );
    void start(void);

    private:
    void setContent(uint8_t row, String content);
    uint8_t _clock_pin;
    uint8_t _data_pin;
    uint8_t _cs_pin;
    uint8_t _dc_pin;
    uint8_t _reset_pin;

    uint8_t lcd_w = 128;
    uint8_t lcd_h = 64;
    u8g2_uint_t margin = 10; //margin

    uint8_t max_title_length = lcd_w-(4*margin);
    uint8_t max_content_length = lcd_w-(2*margin);
    char title_char[];
    char content_char[];
};