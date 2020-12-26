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
        uint8_t clock   = CLOCK,
        uint8_t data    = DATA,
        uint8_t cs      = CS,
        uint8_t dc      = DC,
        uint8_t reset   = RESET
    );
    void setup();
    void start();

    private:
    void draw(const char *t, const char *s);
    void setContent(uint8_t column, uint8_t row, String content);

    char charContent[];
  
};