#include <Servo.h>

#include "../config.h"
#include "./Attitude.h"
#include "./Led.h"

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    class Airplane {

        public:
        
            Servo leftAileronServo;
            Servo rightAileronServo;

            Led infoLed;

            Airplane();

            void tick ();

            void getPitch();
            void getRoll();

    };

#endif