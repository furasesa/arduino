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
        toggleState = !toggleState;
    } else buttonPressed = false;
    if (encoderDelta != 0) { // + (cw) or - (ccw)
        encoderValue = readEncoder();
        // cw changes
        if (encoderDelta > 0){
            counter += 1;
            movement = 1;
        // ccw changes
        } else if (encoderDelta < 0){
            movement = -1;
            counter -= 1;
        }
    } else movement = 0; // steady
}

// Debugger
int16_t encoderValueTest;
bool    toggleStateTest;
int16_t counterTest;
int8_t  movementTest;

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

void Selector::debugToggleState(){
    if (toggleStateTest != toggleState){
        Serial.print("Button State: ");
        Serial.println(toggleState);
        toggleStateTest = toggleState;
    }
    
}

void Selector::debugCounter(){
    if (counterTest != counter) {
        Serial.print("counter: ");
        Serial.println(counter);
        counterTest = counter;
    }
}

void Selector::debugMovement(){
    if (movementTest != movement) {
        if (movement > 0){
            Serial.println("movement: up");
        } else if (movement < 0) {
            Serial.println("movement: down");
        } else if (movement == 0) {
            Serial.println("movement: steady");
        }
        movementTest = movement;
    }
}
void Selector::debugAll(){
    debugButtonSwitch();
    debugToggleState();
    debugEncoderValue();
    debugCounter();
    debugMovement();
}
