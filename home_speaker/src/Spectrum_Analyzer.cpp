#include <Spectrum_Analyzer.h>

MSGEQ7::MSGEQ7(uint8_t Strobe, uint8_t Reset, uint8_t Data, uint8_t Band){
    _str_pin         = Strobe;
    _rst_pin         = Reset;
    _analog_pin      = Data;
    _msgeq7_band     = Band;
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

uint16_t MSGEQ7::read(uint8_t b){
    // uint16_t _spectrum_data[_msgeq7_band];
    digitalWrite      (_str_pin, LOW);
    delayMicroseconds (100);
    _spectrum_data[b] = analogRead(_analog_pin);
    digitalWrite      (_str_pin, HIGH);
    delayMicroseconds (1);

    if (_serial_print){
        Serial.print(_spectrum_data[b]);
        Serial.println(" ");
    }

    return _spectrum_data[b];

    // for (int i = 0; i < _msgeq7_band; i++){
    //     digitalWrite      (_str_pin, LOW);
    //     delayMicroseconds (100);
    //     _spectrum_data[_msgeq7_band] = analogRead(_analog_pin);
    //     digitalWrite      (_str_pin, HIGH);
    //     delayMicroseconds (1);
    // }
    // if (_serial_print){
    //     for (int i = 0; i < _msgeq7_band; i++) {
    //         Serial.print(_spectrum_data[i]);
    //     }
    //     Serial.println(" ");
    // }
}

// uint16_t MSGEQ7::getData(uint8_t band){
//     return _spectrum_data[band];
// }

uint8_t MSGEQ7::msgeq7Band() {
    return _msgeq7_band;
}

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
    _data_out = pin;
    Serial.print("num pixels : ");
    Serial.print(n);
    Serial.print("  ");
    Serial.print("pin : ");
    Serial.print(p);
    Serial.print("  ");
    Serial.print("pixel format : ");
    Serial.print(t);
    Serial.println(" ");
}

bool WS2818::pin_check(uint16_t p){
    Serial.print("is equal to parent? : ");
    Serial.println(_data_out == p);
    return _data_out == p;
}

    /*!
    @brief  set reference data range
    @param  min minimal data value. lower than specified will treat as black
    @param  max maximal data value. set WS2818 color by reference value.
    */
void WS2818::ref_data_range( uint16_t min, uint16_t max) {
        _min_data = min;
        Serial.print("ref_data_range (min) : ");
        Serial.println(_min_data);
        _max_data = max;
        Serial.print("ref_data_range (max) : ");
        Serial.println(_max_data);
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
        Serial.print("starting color : ");
        Serial.println(_start_color);

        _peak_color     = peak_color;
        Serial.print("peak coor : ");
        Serial.println(_peak_color);

        _step_color     = _peak_color - start_color;
        Serial.print("so change color per step : ");
        Serial.println(_step_color);
        
        _level_step     = step;
        Serial.print("total step : ");
        Serial.println(_level_step);
    }

    /*!
    @brief  get led position
    @param  column      num_band as column or pos_x in matrix
    @param  ref_data    data reference from msgeq7 band reading. as row or pos_y in matrix
    @return led position
    */
void WS2818::run(uint8_t column, uint16_t ref_data){
    uint8_t     virtual_y   = roundf(double(ref_data) / double(_max_data) * LED_IN_ROW * _level_step)-1; // 1024/1024*30-1
    uint8_t     led_level   = virtual_y % LED_IN_ROW; //29%5 as led pos y
    uint8_t     led_num     = (column == 0) ? led_level : column*LED_IN_ROW + led_level;
    uint32_t    c_color     = BLUE + (_step_color * virtual_y); // assign color for led pos_y

   
}

// void WS2818::render(){

// }

 /*
    assign to led matrix
            column 0    column 1    column 2    column 3    column 4
    row 4       4           9           14          19          24
    row 3       3           8           13          18          23
    row 2       2           7           12          17          22
    row 1       1           6           11          16          21
    row 0       0           5           10          15          20
    _led_matrix[pos_x][pos_y]
*/





// void WS2818::run(uint16_t data){
//     uint8_t     step_range  = NUM_PIXELS * _level_step;
//     uint16_t    data_range  = _max_data - _min_data; // reference data
//     uint32_t    color_range = _peak_color - _start_color; // spectrum color
//     uint32_t    color_step  = color_range / step_range; // +color per led level
//     uint32_t    color_matrix[NUM_PIXELS][BAND]; // num pixel as row, 

//     // uint16_t    current_data    = 
// }