#include <Spectrum_Analyzer.h>

MSGEQ7::MSGEQ7(uint8_t Strobe, uint8_t Reset, uint8_t Data, uint8_t band){
    _str_pin         = Strobe;
    _rst_pin         = Reset;
    _analog_pin      = Data;
    _msgeq7_band    = band;
}

void MSGEQ7::begin(void){
    if (_str_pin >= 0 && _rst_pin >= 0 && _analog_pin > 0){ //  required pin must be defined
        // MSGEQ7 setup
        pinMode       (_str_pin, OUTPUT);
        pinMode       (_rst_pin, OUTPUT);
        pinMode       (_analog_pin, INPUT);
        // MSGEQ7 init
        digitalWrite  (_rst_pin, HIGH);
        delay(1);
        digitalWrite  (_rst_pin, LOW);
        digitalWrite  (_str_pin, HIGH);
        delay(1);
        if (_serial_print){
            Serial.print("Strobe pin : ");
            Serial.println(_str_pin);
            Serial.print("Reset pin : ");
            Serial.println(_rst_pin);
            Serial.print("Data pin : ");
            Serial.println(_analog_pin);
        }
    } else {
        Serial.println("Pin not configured");
    }
}

void MSGEQ7::read(){
    uint16_t _spectrum_data[_msgeq7_band];
    for (int i = 0; i < _msgeq7_band; i++){
        digitalWrite      (_str_pin, LOW);
        delayMicroseconds (100);
        _spectrum_data[_msgeq7_band] = analogRead(_analog_pin);
        digitalWrite      (_str_pin, HIGH);
        delayMicroseconds (1);
    }
    if (_serial_print){
        for (int i = 0; i < _msgeq7_band; i++) {
            Serial.print(_spectrum_data[i]);
        }
        Serial.println(" ");
    }
}


uint8_t MSGEQ7::msgeq7Band(){
    return _msgeq7_band;
}



uint16_t MSGEQ7::getData(uint8_t band){
    // digitalWrite      (str_pin, LOW);
    // delayMicroseconds (100);
    // _spectrum_data[band] = analogRead(analog_pin);
    // digitalWrite      (str_pin, HIGH);
    // delayMicroseconds (1);
    // if (serial_print){
    //     Serial.print("Band-");
    //     Serial.print(band);
    //     Serial.print(_spectrum_data[band]);
    //     if (band == BAND){ Serial.println(" "); }
    //     else{ Serial.print("  "); }
    // }
    return _spectrum_data[band];
}


// uint16_t* MSGEQ7::spectrum_data(){
//     uint16_t _spectrum_data[msgeq7_band];
//     for (int i = 0; i < msgeq7_band; i++){
//         digitalWrite      (str_pin, LOW);
//         delayMicroseconds (100);
//         _spectrum_data[msgeq7_band] = analogRead(analog_pin);
//         digitalWrite      (str_pin, HIGH);
//         delayMicroseconds (1);
//     }
//     if (serial_print){
//         for (int i = 0; i < msgeq7_band; i++) {
//             Serial.print(_spectrum_data[i]);
//         }
//         Serial.println(" ");
//     }
//     return _spectrum_data;
// }

bool MSGEQ7::monitor_t() {
    return {_serial_print = !_serial_print};
}












/*!
  @brief   Child class of Adafruit_NeoPixel
  @param   n  Total Pixels
  @param   p  Pin Number
  @param   t  See Neopixel doc. predefined value PIXEL_FORMAT
  @return  Adafruit_NeoPixel object
*/
WS2818::WS2818 ( uint8_t n, uint8_t p, neoPixelType t) : Adafruit_NeoPixel ( n, p, t) {
    data_out = pin;
    // begin();
}



    /*!
    @brief  set reference data range
    @param  min minimal data value. lower than specified will treat as black
    @param  max maximal data value. set WS2818 color by reference value.
    */
void WS2818::ref_data_range( uint16_t min, uint16_t max) {
        _min_data = min;
        _max_data = max;
    }

    /*!
    @brief  set color changes by reading reference value. 32bit color
    @param  start_color the color once min reference specified.
    @param  peak_color  the color when max reference reach out.
    @param  step        1 step mean last led will be peak color.
    total lead in strip * step = total indicator level
    */
void WS2818::ref_color_range(
    uint32_t start_color,
    uint32_t peak_color, 
    uint8_t step) {
        _start_color    = start_color;
        _peak_color     = peak_color;
        _level_step     = step;
    }



// void WS2818::run(uint16_t data){
//     uint8_t     step_range  = NUM_PIXELS * _level_step;
//     uint16_t    data_range  = _max_data - _min_data; // reference data
//     uint32_t    color_range = _peak_color - _start_color; // spectrum color
//     uint32_t    color_step  = color_range / step_range; // +color per led level
//     uint32_t    color_matrix[NUM_PIXELS][BAND]; // num pixel as row, 

//     // uint16_t    current_data    = 
// }