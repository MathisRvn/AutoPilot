// TODO : Refaire le code de la partie recepetion

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

    typedef enum SwitchMode {
        SWITCH_OFF, SWITCH_UP, SWITCH_MIDDLE, SWITCH_DOWN
    } SwitchMode;

    class ReceiverSwitch {

        public:
            ReceiverPwmChannel *receiverPwmChannel;
            SwitchMode switchMode;

            ReceiverSwitch(ReceiverPwmChannel *initial_receiverPwmChannel);
            void checkMode();
    };

#endif