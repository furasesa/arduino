#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include "pins.h"

class Selector : public AiEsp32RotaryEncoder {
    public:
    Selector(
        uint8_t A   = ROTARY_ENCODER_A_PIN, 
        uint8_t B   = ROTARY_ENCODER_B_PIN, 
        uint8_t SW  = ROTARY_ENCODER_BUTTON_PIN
        );
    
    void    listenEncoderChanges();

    void    debugEncoderValue();
    void    debugButtonSwitch();
    void    debugAll();

    // private: 
    bool    buttonPressed   = false;
    int16_t encoderValue    = 0;
    int16_t encoderDelta    = 0;
};