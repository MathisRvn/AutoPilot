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
        attachPCINT(digitalPinToPCINT(pin), callback, RISING);
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

#ifdef ENABLE_RECEIVER_FILTERING
    void Receiver::tick() {

        for (short i = 0; i < 2; i++) {


            // TODO remove not static variables in for loops

            // Updating the list of the last ten values
            previous[i][previous_index[i]] = ch[i];
            previous_index[i] = (previous_index[i] + 1) % 10;

            // Filtering the values by taking the average of the last ten values
            filtered[i] = 0;

            for (short j = 0; j < 10; j++) {
                filtered[i] += previous[i][j];
            }

            filtered[i] /= 10;

        }

    }
#endif


void Receiver::print(void) {

    Serial.print("Cmd:");
    Serial.print(ch[0]);
    Serial.print(',');
    Serial.print(ch[1]);
    Serial.print(',');
    Serial.print(ch[2]);
    Serial.print(',');
    Serial.print(ch[3]);
    Serial.print(',');
    Serial.print(ch[4]);
    Serial.print(',');
    Serial.print(ch[5]);
    Serial.println();

};