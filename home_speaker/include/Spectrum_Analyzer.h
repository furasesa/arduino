#ifndef SPECTRUM_ANALYZER_H
#define SPECTRUM_ANALYZER_H

#include <Adafruit_NeoPixel.h>
#include <definition.h>
#include <color_palette.h>
#include <math.h>


#define PIXEL_FORMAT NEO_RGB + NEO_KHZ800

class MSGEQ7{
    public:
    MSGEQ7 (
        uint8_t Strobe  = STROBE, 
        uint8_t Reset   = RESET, 
        uint8_t Data    = ANALOG_PIN,
        uint8_t Band    = BAND 
        );

    void        begin           (void);
    uint16_t    read            (uint8_t);
    // uint16_t    getData      (uint8_t band); 
    uint8_t     msgeq7Band      ();
    // bool        monitor_t       ();
    
    private:
    uint8_t     _str_pin;
    uint8_t     _rst_pin;
    uint8_t     _analog_pin;
    bool        _serial_print {};
    uint16_t    _spectrum_data[]; 
    uint8_t     _msgeq7_band;
};

class WS2818:public Adafruit_NeoPixel {
    public:
    WS2818  ( 
        uint8_t num_pixel = NUM_PIXELS, 
        uint8_t pin = LD1, 
        neoPixelType pixel_format = NEO_RGB + NEO_KHZ800);

    void ref_data_range     (
        uint16_t min = MIN_SPECTRUM_VALUE, 
        uint16_t max = MAX_SPECTRUM_VALUE);
    
    void ref_color_range    (
        uint32_t start_color = BLUE,
        uint32_t peak_color = RED, 
        uint8_t step = COLOR_DIFF_LEVEL);

    void run    (
        uint8_t c,
        uint16_t ref_data);

    void runTest  (int n);
    

    void pin_check  (uint16_t);
    // bool monitor_t  ();

    private:
    uint16_t    _data_out;
    uint16_t    _min_data;
    uint16_t    _max_data;
    uint32_t    _start_color;
    uint32_t    _peak_color;
    uint32_t    _step_color;
    uint32_t    _level_step;
    bool        _serial_print {};
};


#endif