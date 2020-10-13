#include <Spectrum_Analyzer.h>

MSGEQ7::MSGEQ7(uint8_t Strobe, uint8_t Reset, uint8_t Data, uint8_t Band){
    _str_pin         = Strobe;
    _rst_pin         = Reset;
    _analog_pin      = Data;
    _msgeq7_band     = Band;
}

void MSGEQ7::begin(void){
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
    #ifdef DEBUG
        Serial.print("Strobe pin : ");
        Serial.println(_str_pin);
        Serial.print("Reset pin : ");
        Serial.println(_rst_pin);
        Serial.print("Data pin : ");
        Serial.println(_analog_pin);
    #endif
}

uint16_t MSGEQ7::read(uint8_t b){
    // uint16_t _spectrum_data[_msgeq7_band];
    digitalWrite      (_str_pin, LOW);
    delayMicroseconds (100);
    _spectrum_data[b] = analogRead(_analog_pin);
    digitalWrite      (_str_pin, HIGH);
    delayMicroseconds (1);
    #ifdef DEBUG
        Serial.print("Band_");
        Serial.print(b);
        Serial.print(": ");
        Serial.print(_spectrum_data[b]);
        Serial.print("  ");
    #endif
    return _spectrum_data[b];
}

uint8_t MSGEQ7::msgeq7Band() {
    return _msgeq7_band;
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
    #ifdef DEBUG
        Serial.print("num pixels : ");
        Serial.print(n);
        Serial.print("  ");
        Serial.print("pin : ");
        Serial.print(p);
        Serial.print("  ");
        Serial.print("pixel format : ");
        Serial.print(t);
        Serial.println(" ");
    #endif
}

void WS2818::pin_check(uint16_t p){
    #ifdef DEBUG
        Serial.print("pin assigned : ");
        Serial.print(_data_out);
        Serial.println(p);
    #endif
    // return _data_out == p;
}

    /*!
    @brief  set reference data range
    @param  min minimal data value. lower than specified will treat as black
    @param  max maximal data value. set WS2818 color by reference value.
    */
void WS2818::ref_data_range( uint16_t min, uint16_t max) {
        _min_data = min;
        _max_data = max;
        #ifdef DEBUG
            Serial.print("ref_data_range (min) : ");
            Serial.println(_min_data);
            Serial.print("ref_data_range (max) : ");
            Serial.println(_max_data);
        #endif
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
        _step_color     = (_peak_color - start_color) / (LED_IN_ROW * COLOR_DIFF_LEVEL) ;
        _level_step     = step;

        #ifdef DEBUG
            Serial.print("starting color : ");
            Serial.println(_start_color);
            Serial.print("peak color : ");
            Serial.println(_peak_color);
            Serial.print("so change color per step : ");
            Serial.println(_step_color);
            Serial.print("total step : ");
            Serial.println(_level_step);
        #endif
    }

    /*!
    @brief  run         calculate based from band and reference data
    @param  column      MSGEQ7 band as column.
    @param  ref_data    reference data from msgeq7 band reading
    */
void WS2818::run(uint8_t column, uint16_t ref_data){
    #ifdef DEBUG
        Serial.print(" -band : ");
        Serial.print(column);
        Serial.print("  -ref_data : ");
        Serial.println(float(ref_data));
    #endif
    // virtual_led is led's length logic.
    // _min_data and _max_data are set from WS2818::ref_data_range. MSGEQ7 data max = 1024, min = 30
    // (ref_data-min_data) / (max_data-min_data) * LED_IN_ROW * level step
    // assume that ref_data =  1024; SO (1024-30) / (1024-30) * 5 * 6 - 1;
    // virtual led range 0-29;
    
    // float _ref_data = (ref_data > 50) ? ref_data - _min_data : ref_data;
    if (ref_data < _min_data){
        ref_data = _min_data;
    }

    uint8_t    virtual_led = float(ref_data * LED_IN_ROW * COLOR_DIFF_LEVEL) / float(_max_data) -1.0f; // 1024/1024*30-1

    // because only LED_IN_ROW which will be shows, so virtual_led % LED_IN_ROW
    // led_pos is led_position / cursor to set led.
    // assume max virtual_led = 29; so 29%5 = 4. 
    uint8_t     led_pos     = virtual_led % LED_IN_ROW;

    // led_num is led_number. in led_series, column +1 is same to +LED_IN_ROW. column = spectrum analyzer band
    // band 0 -> led 0-4, band 1 led 5-9, band 2 -> led 10-14, etc
    uint8_t     led_num     = (column == 0) ? led_pos : column*LED_IN_ROW + led_pos; 

    // c_color : current_color. Is color that assign to current virtual led then shown by led_num
    uint32_t    c_color     = BLUE + (_step_color * virtual_led);

    for (int i = 0; i < LED_IN_ROW; i++) {
        // starting current level bellow than LED_IN_ROW
        if (virtual_led < LED_IN_ROW){
            // led_num 0-4 assign color as c_color
            // over led number will be WS2818::clear() or black
            led_pos     = virtual_led;
        } else { 
            // assign black color as previous color
            if (led_pos < 0){ // led_num 0 as c_color
                led_pos = 4;
            } else {
                led_pos = virtual_led % LED_IN_ROW;
            }
        }

        // re-calculate 
        led_num     = (column == 0) ? led_pos : column*LED_IN_ROW + led_pos;
        c_color     = BLUE + (_step_color * virtual_led);
        #ifdef DEBUG
            Serial.print    (" -virtual led : ");
            Serial.print    (virtual_led);
            Serial.print    ("  -led pos : ");
            Serial.print    (led_pos);
            Serial.print    ("  -led num : ");
            Serial.print    (led_num);
            Serial.print    ("  -color : ");
            Serial.println    (c_color);
        #endif
        setPixelColor(led_num, c_color);
        if (virtual_led <= 0) {
            virtual_led = 0;
        } else {
            virtual_led--;
        }
    }
}

void WS2818::runTest(int n) {
    for (int r=1; r < 11; r++){
      int ref = r*100;
      run(n, ref);
      show();
    }
}

// bool WS2818::monitor_t(){
//     return {_serial_print = !_serial_print};
// }
