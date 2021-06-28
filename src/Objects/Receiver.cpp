#include <Arduino.h>
#include <PinChangeInterrupt.h>

#include "Receiver.h"

ReceiverPwmChannel::ReceiverPwmChannel (int initial_pin, void(*callback)(void)) {
    pin = initial_pin;
    last_change = micros();
    pinMode(pin, INPUT);
	attachPCINT(digitalPinToPCINT(pin), callback, CHANGE);
}

void ReceiverPwmChannel::interruptCallback(void) {
    unsigned long now = micros();
    unsigned long v = now - last_change;
    if (v < 5000) {
        value = v;
    }
    last_change = now;
}


ReceiverSwitch::ReceiverSwitch(ReceiverPwmChannel *initial_receiverPwmChannel) {
    initial_receiverPwmChannel = initial_receiverPwmChannel;
    checkMode();
}

void ReceiverSwitch::checkMode() {
    if (receiverPwmChannel->value < 500) {
        switchMode = SWITCH_OFF;
    } else if (receiverPwmChannel->value < 1200) {
        switchMode = SWITCH_UP;
    } else if (receiverPwmChannel->value < 1700) {
        switchMode = SWITCH_MIDDLE;
    } else if (receiverPwmChannel->value < 2200) {
        switchMode = SWITCH_DOWN;
    } else { // shouldn't happen
        switchMode = SWITCH_UP; // up bind to manual control in basic config
    }
}