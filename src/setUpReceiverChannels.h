#include "./config.h"

#ifndef SET_UP_RECEIVER_CHANNEL_H
    #define SET_UP_RECEIVER_CHANNEL_H

    #ifdef CH1_INPUT
        void ch1Interrupt();
    #endif

    #ifdef CH2_INPUT
        void ch2Interrupt();
    #endif

    #ifdef CH3_INPUT
        void ch3Interrupt();
    #endif

    #ifdef CH4_INPUT
        void ch4Interrupt();
    #endif

    #ifdef CH5_INPUT
        void ch5Interrupt();
    #endif

    #ifdef CH6_INPUT
        void ch6Interrupt();
    #endif

#endif