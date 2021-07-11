#include <Arduino.h>

#include "./config.h"

#include "./error.h"

void configurationError () {
    #ifdef ENABLE_DEBUG
        Serial.println("CONFFIGURATION ERROR");
    #endif
    delay(500); // Enable the watchdog and reset the board
}