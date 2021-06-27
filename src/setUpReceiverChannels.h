#include "./config.h"

#ifndef SET_UP_RECEIVER_CHANNEL_H
    #define SET_UP_RECEIVER_CHANNEL_H

    void aileronInterrupt();

    void elevatorInterrupt();

    void throttleInterrupt();

    void rudderInterrupt();

    #ifdef SWITCH1_INPUT
        void switch1Interrupt();
    #endif

    #ifdef SWITCH2_INPUT
        void switch2Interrupt();
    #endif

#endif