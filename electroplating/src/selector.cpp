#include "selector.h"

Selector::Selector(
    uint8_t A, uint8_t B, uint8_t SW ) : AiEsp32RotaryEncoder (A, B, SW) {}

// function
void Selector::listenEncoderChanges(){ 
    // set encoderDelta
    encoderDelta = encoderChanged();

    // Button and Toggle function
    if (currentButtonState() == BUT_RELEASED) {
        buttonPressed = true;
    } else buttonPressed = false;
    if (encoderDelta != 0) encoderValue = readEncoder();
}

// Debugger
int16_t encoderValueTest;
void Selector::debugEncoderValue(){
    if (encoderValueTest != encoderValue){
        encoderValueTest = encoderValue;
        Serial.print("EncoderVal :");
        Serial.println(encoderValue);
    }
}

void Selector::debugButtonSwitch(){
    if (buttonPressed) Serial.println("button clicked");
}

void Selector::debugAll(){
    debugButtonSwitch();
    debugEncoderValue();
}
