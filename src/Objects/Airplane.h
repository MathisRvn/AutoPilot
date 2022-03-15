#include <Servo.h>

#include "../config.h"
#include "./Receiver.h"
#include "./Attitude.h"
#include "./Led.h"

#ifndef AIRPLANE_H
    #define ACTUATORS_H

    class Airplane {

        public:
        
            Servo leftAileronServo;
            Servo rightAileronServo;

            Receiver *receiver;

            Led infoLed;

            Airplane(Receiver *initial_receiver);

            void tick ();

            void getPitch();
            void getRoll();

    };

#endif