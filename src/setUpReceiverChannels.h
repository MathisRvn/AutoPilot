#include "./config.h"

#ifndef SET_UP_RECEIVER_CHANNEL_H
    #define SET_UP_RECEIVER_CHANNEL_H

    extern ReceiverPwmChannel aileronReceiver;
    void aileronInterrupt();

    extern ReceiverPwmChannel elevatorReceiver;
    void elevatorInterrupt();

    extern ReceiverPwmChannel throttleReceiver;
    void throttleInterrupt();

    extern ReceiverPwmChannel rudderReceiver;
    void rudderInterrupt();

    extern ReceiverPwmChannel switch1Receiver;
    void switch1Interrupt();

    extern ReceiverPwmChannel switch2Receiver;
    void switch2Interrupt();

#endif