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