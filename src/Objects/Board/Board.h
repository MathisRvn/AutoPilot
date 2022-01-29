#include "../Led.h"

#include "../../config.h"

#ifndef BOARD_H
    #define BOARD_H

    class Board {

        public:
            Led infoLed;

            Board() : infoLed(BOARD_LED_PIN, LED_SLOW_BLINK) {};

    };

#endif