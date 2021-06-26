#ifndef LED_H
    #define LED_H

    typedef enum LedStatus { 
        OFF, ON, SLOW_BLINK, FAST_BLINK 
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