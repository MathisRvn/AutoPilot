#ifndef RECEIVER_H
    #define RECEIVER_H

    class ReceiverPwmChannel {

        public:
            int pin;
            int value;
            unsigned long last_change;

            ReceiverPwmChannel(int initial_pin, void(*callback)(void));

            void interruptCallback(void);

    };

#endif