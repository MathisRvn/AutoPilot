#include "../config.h"

#include "./Receiver.h"

#if RECEIVER_PIN == 2 || RECEIVER_PIN == 3

    #error "HARDWARE INTERRUPT NOT DEVELOPPED YET"

#else

    #include <PinChangeInterrupt.h>

    Receiver::Receiver (int initial_pin, void(*callback)(void)) {
        pin = initial_pin;
        last_time_receiver_fall = micros();
        pinMode(pin, INPUT);
        attachPCINT(digitalPinToPCINT(pin), callback, CHANGE);
    }

#endif

void Receiver::interruptCallback(void) {
    receiver_now = micros();
    receiver_delta = receiver_now - last_time_receiver_fall;
    last_time_receiver_fall = receiver_now;

    if (receiver_delta > 5000) {
        i = 0;  
    }else{
        if (i < 6) {
            ch[i] = receiver_delta;
            i += 1;  
        }  
    }
}