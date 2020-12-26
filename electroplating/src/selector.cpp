#include "selector.h"

Selector::Selector(
    uint8_t A, uint8_t B, uint8_t SW ) : AiEsp32RotaryEncoder (A, B, SW) {
    // no-op
}

void Selector::listenEncoder(){
    //lets see if anything changed
	int16_t encoderDelta = encoderChanged();
    if (currentButtonState() == BUT_RELEASED) swState = !swState;
	// if value is changed compared to our last read
	if (encoderDelta != 0) {
        encoderValue =  readEncoder();
        // +value to up and counter+, 0 is steady, viceversa
        // cw changes
        if (encoderDelta > 0){
            counter += 1;
            movement = 1;
        // ccw changes
        } else if (encoderDelta < 0){
            counter -= 1;
            movement = -1;
        
        }
    //no rotation
    } else movement = 0;
}

bool newSwState;
bool Selector::getSwitchState(){
    if (newSwState != swState){
        Serial.print("switch state: ");
        Serial.println(swState);
        newSwState = swState;
        return newSwState;
    }
    return swState;
}

int8_t newMovement;
int8_t Selector::getMovement(){
    // print movement
    if (newMovement != movement) {
        newMovement = movement;
        if (newMovement > 0){
            Serial.println("movement: up");
        } else if (newMovement < 0) {
            Serial.println("movement: down");
        } else if (newMovement == 0) {
            Serial.println("movement: steady");
        }
        return newMovement;
    }
    return movement;
}


int16_t newCounter;
int16_t Selector::getCounter() {
    // print counter
    if (newCounter != counter) {
        Serial.print("counter: ");
        Serial.println(counter);
        newCounter = counter;
        return newCounter;
    }
    return counter;
}

int16_t newEncoderValue;
int16_t Selector::getEncoderValue(){
    if (newEncoderValue != encoderValue){
        Serial.print("encoder value: ");
        Serial.println(encoderValue);
        newEncoderValue = encoderValue;
        return newEncoderValue;
    }
    return encoderValue;
}


