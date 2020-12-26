#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include "pins.h"


// AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(
//   ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN);


// void setup(){
//     //we must initialize rorary encoder 
// 	rotaryEncoder.begin();
// 	rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();});
// 	//optionally we can set boundaries and if values should cycle or not
// 	rotaryEncoder.setBoundaries(0, 10, true); //minValue, maxValue, cycle values (when max go to min and vice versa)
// }

// void rotary_loop() {
// 	//first lets handle rotary encoder button click
// 	if (rotaryEncoder.currentButtonState() == BUT_RELEASED) {
// 		//we can process it here or call separate function like:
// 		//rotaryEncoder.reset();
//     //rotaryEncoder.disable();
//     rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
//     test_limits *= 2;
// 	}
// 	//lets see if anything changed
// 	int16_t encoderDelta = rotaryEncoder.encoderChanged();
	
// 	//optionally we can ignore whenever there is no change
// 	// if (encoderDelta == 0) return;
	
// 	//if value is changed compared to our last read
// 	if (encoderDelta!=0) {
// 		//now we need current value
// 		int16_t encoderValue = rotaryEncoder.readEncoder();
// 		//process new value. Here is simple output.
//     String(encoderValue).toCharArray(encoder_value,3);
//     u8g2.drawStr(50,30, encoder_value);
// 		Serial.print("Value: ");
// 		Serial.println(encoderValue);
// 	} 
	
// }

class Selector : public AiEsp32RotaryEncoder {
    public:
    Selector(
        uint8_t A   = ROTARY_ENCODER_A_PIN, 
        uint8_t B   = ROTARY_ENCODER_B_PIN, 
        uint8_t SW  = ROTARY_ENCODER_BUTTON_PIN
        );
    
    void    listenEncoder();
    bool    getSwitchState();
    int8_t  getMovement();
    int16_t getCounter();
    int16_t getEncoderValue();
    

    private:
    bool    swState     = false;
    int8_t  movement    = 0;
    int16_t counter     = 0;
    int16_t encoderValue = 0;
};