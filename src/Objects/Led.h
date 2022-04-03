#include "../config.h"

#ifndef LED_H
    #define LED_H

    typedef enum LedStatus { 
        LED_OFF, LED_ON, LED_SLOW_BLINK, LED_FAST_BLINK 
    } LedStatus;

    class Led {

        public:

            int pin;
            LedStatus status;
            unsigned long last_rising_edge;

            Led (int initialPin, LedStatus initalStatus);
            void tickLed ();
            
    };

#endif
