#include <Arduino.h>

#include "../config.h"

#include "./Led.h"

Led::Led (int initialPin, LedStatus initalStatus) {
    pinMode(initialPin, OUTPUT);
    pin = initialPin;
    status = initalStatus;
    last_rising_edge = millis();
    tickLed();
}

void Led::tickLed () {
    
    if (status == ON) {
        digitalWrite(pin, HIGH);
    } else if (status == OFF) {
        digitalWrite(pin, LOW);
    } else {

        unsigned long now = millis();
        if (status == SLOW_BLINK) {

            if (now - last_rising_edge > 2 * SLOW_BLINK_FREQUENCY) {
                last_rising_edge = now;
                digitalWrite(pin, HIGH);
            } else if (now - last_rising_edge > SLOW_BLINK_FREQUENCY) {
                digitalWrite(pin, LOW);
            }

        } else { // == FAST_BLINK

            if (now - last_rising_edge > 2 * FAST_BLINK_FREQUENCY) {
                last_rising_edge = now;
                digitalWrite(pin, HIGH);
            } else if (now - last_rising_edge > FAST_BLINK_FREQUENCY) {
                digitalWrite(pin, LOW);
            }

        }

    }

}